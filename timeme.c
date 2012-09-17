/*
*	timeme.c
*	calcs how long a command takes to complete
*	mrzammler@gmail.com
*/

#include <stdio.h>
#include <proto/timer.h>
#include <exec/memory.h>

void delete_timer ( struct timerequest *tr )
{
    struct MsgPort *tp;

    if ( tr != 0 )
    {
        tp = tr->tr_node.io_Message.mn_ReplyPort;

        if ( tp != 0 )
            DeletePort ( tp );

        CloseDevice ( ( struct IORequest * ) tr );
        DeleteExtIO ( ( struct IORequest * ) tr );
    }
}

struct timerequest *create_timer ( ULONG unit )
{
    /* return a pointer to a timer request.  If any problem, return NULL */
    LONG error;
    struct MsgPort *timerport;
    struct timerequest *TimerIO;

    timerport = ( struct MsgPort * ) CreatePort ( 0, 0 );
    if ( timerport == NULL )
        return ( NULL );

    TimerIO = ( struct timerequest * )
              CreateExtIO ( timerport, sizeof ( struct timerequest ) );
    if ( TimerIO == NULL )
    {
        DeletePort ( timerport );   /* Delete message port */
        return ( NULL );
    }

    error = OpenDevice ( TIMERNAME, unit, ( struct IORequest * ) TimerIO, 0L );
    if ( error != 0 )
    {
        delete_timer ( TimerIO );
        return ( NULL );
    }
    return ( TimerIO );
}

LONG get_sys_time ( struct timeval *tv )
{
    struct timerequest *tr;
    tr = create_timer ( UNIT_MICROHZ );

    /* non zero return says error */
    if ( tr == 0 )
        return ( -1 );

    tr->tr_node.io_Command = TR_GETSYSTIME;
    DoIO ( ( struct IORequest * ) tr );

    /* structure assignment */
    *tv = tr->tr_time;

    delete_timer ( tr );
    return ( 0 );
}

void error_exit ( char *msg )
{
    printf ( "%s\n", msg );
    exit ( 0 );
}

int main ( int argc, char **argv )
{
    struct Library * TimerBase;
    int size=0,i,h=0,m=0,ml=0,s=0;
    char *exec;
    struct timeval time1, time2;
    struct timerequest *tr;

    if ( argc <= 1 )
    {
        printf ( "timeme 1.0 - Times how long a command takes to execute.\n" );
        printf ( "Usage: timeme (command) [params] ...\nContact: mrzammler@freemail.gr\n" );
        exit ( 0 );
    }

    /* count the arguments */
    for ( i=1;i<argc;i++ ) size += strlen ( argv[i] );
    size += argc-2;
    exec = ( char * ) AllocMem ( size+1, MEMF_PUBLIC|MEMF_CLEAR );

    /* build the execute line */
    sprintf ( exec, "%s", argv[1] );
    for ( i=2;i<argc;i++ )
    {
        sprintf ( exec, "%s %s", exec, argv[i] );
    }

    if ( get_sys_time ( &time1 ) ) error_exit ( "Error getting timer.device." );
    ( void ) Execute ( exec, 0,0 );
    if ( get_sys_time ( &time2 ) ) error_exit ( "Error getting timer.device." );

    if ( ! ( tr = create_timer ( UNIT_MICROHZ ) ) ) error_exit ( "Error getting timer.device." );
    TimerBase = ( struct Library * ) tr->tr_node.io_Device;
    SubTime ( &time2,&time1 );
    TimerBase = ( struct Library * ) ( -1 );
    delete_timer ( tr );
    h = time2.tv_secs/3600;
    m = time2.tv_secs/60;
    ml = m%60;

    printf ( "\n-- %d hours, %d minutes, %ld secs, %ld msec --\n", h,ml,time2.tv_secs%60,time2.tv_micro );
    FreeMem ( exec, size+1 );
    exit ( 0 );

}
