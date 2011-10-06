/**
 * ReadArduino - reads a line of text sent to /dev/ttyUSB1 by the battery monitoring
 * Arduino over ZigBee and prints the line along with a time stamp.
 * 
 * @author Warwick Hunter
 * @since  2011-10-06
 */
File tty = new File("/dev/ttyUSB1")
Calendar time = Calendar.getInstance()
tty.eachLine { line ->
    time.setTimeInMillis(System.currentTimeMillis())
    printf '%1$tF %1$tT %2$s %n', time, line
}

