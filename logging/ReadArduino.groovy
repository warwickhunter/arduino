#!/usr/bin/env groovy
/**
 * ReadArduino - reads a line of text sent to a terminal such as /dev/ttyUSB1 
 * by the battery monitoring Arduino over ZigBee and prints the line along with 
 * a time stamp.
 * 
 * @author Warwick Hunter
 * @since  2011-10-06
 */

def cli = new CliBuilder()
cli.h(longOpt:'help', 'Usage information')
cli.t(longOpt:'tty', 'The terminal device to open, e.g. /dev/ttyUSB0', required:true, args:1, type:String)
 
def options = cli.parse(args)
if (!options) {
    return
}
if (options.h) {
    cli.usage()
}
 
File tty = new File(options.tty)
Calendar time = Calendar.getInstance()
tty.eachLine { line ->
    if (line.length() > 0) {
        time.setTimeInMillis(System.currentTimeMillis())
        printf '%1$tF %1$tT %2$s %n', time, line
    }
}

