#! /bin/sh
#
# cmsdd	       Start/Stop the CMSD daemon
#
# chkconfig: 345 20 80
# description:	The cmsd daemon runs the XRD control network.
#
# processname: cmsd
# pidfile: /var/run/cmsd.pid
# config:

CMSD=$ROOTSYS/bin/cmsd
CMSDLIBS=@libdir@

# Source function library.
. /etc/init.d/functions

# Get config.
. /etc/sysconfig/network

# Get cmsd config
[ -f /etc/sysconfig/cmsd ] && . /etc/sysconfig/cmsd

# Configure the environment
[ ! -z "$CMSDENVCONFIG" ] && [ -f "$CMSDENVCONFIG" ] && . $CMSDENVCONFIG

# Check that networking is up.
if [ ${NETWORKING} = "no" ]
then
	exit 0
fi

[ -x $CMSD ] || exit 0

RETVAL=0
prog="cmsd"

start() {
        echo -n $"Starting $prog: "
        # Options are specified in /etc/sysconfig/cmsd .
        # $CMSDUSER *must* be the name of an existing non-privileged user.
        export LD_LIBRARY_PATH=$CMSDLIBS:$LD_LIBRARY_PATH
        daemon $CMSD -b -l $CMSDLOG -R $CMSDUSER -c $CMSDCF $CMSDDEBUG
        RETVAL=$?
        echo
        [ $RETVAL -eq 0 ] && touch /var/lock/subsys/cmsd
        return $RETVAL
}

stop() {
	[ ! -f /var/lock/subsys/cmsd ] && return 0 || true 
        echo -n $"Stopping $prog: "
        killproc cmsd
        RETVAL=$?
        echo
        [ $RETVAL -eq 0 ] && rm -f /var/lock/subsys/cmsd
	return $RETVAL
}

# See how we were called.
case "$1" in
  start)
	start
	;;
  stop)
	stop
	;;
  status)
	status cmsd
	RETVAL=$?
	;;
  restart|reload)
	stop
	start
	;;
  condrestart)
	if [ -f /var/lock/subsys/cmsd ]; then
            stop
            start
        fi
	;;
  *)
	echo  $"Usage: $0 {start|stop|status|restart|reload|condrestart}"
	exit 1
esac

exit $RETVAL
