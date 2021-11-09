#!/bin/sh

JAVA_HOME="/usr/lib/jvm/java-1.8-openjdk"
JAVA_JAR_ENTRY_POINT="org.multimc.EntryPoint"
JAVA_COMPILE_FLAGS="-target 1.6 -source 1.6 -Xlint:deprecation -Xlint:unchecked"

SRC="org/multimc/EntryPoint.java \
    org/multimc/Launcher.java \
    org/multimc/LegacyFrame.java \
    org/multimc/NotFoundException.java \
    org/multimc/ParamBucket.java \
    org/multimc/ParseException.java \
    org/multimc/Utils.java \
    org/multimc/onesix/OneSixLauncher.java \
    net/minecraft/Launcher.java \
"

OUT="NewLaunch.jar"

rm -r */*/*.class
"$JAVA_HOME/bin/javac" $JAVA_COMPILE_FLAGS $SRC
OBJS="$(find -name "*.class" | tr '\n' ' ')"
"$JAVA_HOME/bin/jar" cfm "$OUT" manifest.txt $OBJS
