;========== MEASURES SUN =============

[MeasureSunriseHour]
Measure=String
String=[@ForecastTodaySunriseTime]
RegExpSubstitute=1
Substitute="^(\d{1,2}):\d{1,2}$":"\1","^$":"0"
DynamicVariables=1

[MeasureSunriseMinute]
Measure=String
String=[@ForecastTodaySunriseTime]
RegExpSubstitute=1
Substitute="^\d{1,2}:(\d{1,2})$":"\1","^$":"0"
DynamicVariables=1

[MeasureSunriseMoment]
Measure=Calc
Formula=( 60 * [MeasureSunriseHour] + [MeasureSunriseMinute] )
DynamicVariables=1
FinishAction=[!UpdateMeasure MeasureTimeSUN]

[MeasureSunsetHour]
Measure=String
String=[@ForecastTodaySunsetTime]
RegExpSubstitute=1
Substitute="^(\d{1,2}):\d{1,2}$":"\1","^$":"0"
DynamicVariables=1

[MeasureSunsetMinute]
Measure=String
String=[@ForecastTodaySunsetTime]
RegExpSubstitute=1
Substitute="^\d{1,2}:(\d{1,2})$":"\1","^$":"0"
DynamicVariables=1

[MeasureSunsetMoment]
Measure=Calc
Formula=( 60 * [MeasureSunsetHour] + [MeasureSunsetMinute] )
DynamicVariables=1
FinishAction=[!UpdateMeasure MeasureTimeSUN]

[MeasureHour]
Measure=Time
Format=%#H

[MeasureMinute]
Measure=Time
Format=%M

[MeasureDayLengthSUN]
Measure=Calc
Formula=( MeasureSunsetMoment - MeasureSunriseMoment )

;Position
[MeasureSinceSunrise]
Measure=Calc
Formula=(( 60 * MeasureHour + MeasureMinute - MeasureSunriseMoment ) / ( 0.00001 + MeasureDayLengthSUN ))

;==FORCE REFRESHES FOR SUNSET/SUNRISE/DAYCHANGE     ---    [!Delay 2000][!Refresh][!Delay 2000]    replaces !update==
[MeasureTime2]
Measure=Time
Format=%H:%M:%S
IfMatch=(?si)#SunsetTime#:00
IfMatchAction=[!UpdateMeasure MeasureSinceMoonrise][!UpdateMeasure MeasureTimeMOON][!UpdateMeter MeterMoon][!Redraw][!Update][!Log "Weather skin: Refresh at sunset for moon"]
UpdateDivider=1
DynamicVariables=1

[MeasureTime4]
Measure=Time
Format=%H:%M:%S
IfMatch=(?si)#SunriseTime#:00
IfMatchAction=[!UpdateMeasure MeasureSinceMoonrise][!UpdateMeasure MeasureTimeMOON][!UpdateMeter MeterMoon][!Redraw][!Update][!Log "Weather skin: Refresh at sunrise for moon"]
UpdateDivider=1
DynamicVariables=1

;Refresh on day change (turn on computer)
[MeasureDayChange]
Measure=Time
Format=%d
OnChangeAction=[!UpdateMeasure MeasureSinceMoonrise][!UpdateMeasure MeasureTimeMOON][!UpdateMeter MeterMoon][!Redraw][!Update][!Log "Weather skin: New day, Refresh weather."]

;Refresh on sunrise/set variable change (computer off during sunrise/sunset) , doesnt work the best right now
[MeasureSunChange]
Measure=Calc
Format=#Daytime#
OnChangeAction=[!UpdateMeasure MeasureSinceMoonrise][!UpdateMeasure MeasureTimeMOON][!UpdateMeter MeterMoon][!Redraw][!Update][!Log "Weather skin: Sun change, Refresh weather."]

;Set Daytime variable and check if moon should be shown now.
[MeasureTimeSUN]
Measure=Calc
Formula=( 60 * MeasureHour + MeasureMinute )
IfCondition=((#CURRENTSECTION#>=MeasureSunriseMoment)&&(#CURRENTSECTION#<MeasureSunsetMoment))
IfTrueAction=[!SetVariable Daytime "1"][!WriteKeyValue Variables Daytime "1" "#@#Variables.inc"][!Delay 500][!ShowMeter "MeterSun"][!UpdateMeasure MeasureTimeMOON][!UpdateMeter MeterMoon][!Redraw]
IfFalseAction=[!SetVariable Daytime "0"][!WriteKeyValue Variables Daytime "0" "#@#Variables.inc"][!Delay 500][!HideMeter "MeterSun"][!UpdateMeasure MeasureTimeMOON][!UpdateMeter MeterMoon][!Redraw]
DynamicVariables=1

;========== MOON CALCULATIONS =============

[MeasureMoonriseHour]
Measure=String
String=[@MoonDay1RiseTime]
RegExpSubstitute=1
Substitute="^(\d{1,2}):\d{1,2}$":"\1","^$":"0"
DynamicVariables=1

[MeasureMoonriseMinute]
Measure=String
String=[@MoonDay1RiseTime]
RegExpSubstitute=1
Substitute="^\d{1,2}:(\d{1,2})$":"\1","^$":"0"
DynamicVariables=1

;***ERROR: Calc: "N" is unknown***
[MeasureMoonriseMoment]
Measure=Calc
Formula=( 60 * [MeasureMoonriseHour] + [MeasureMoonriseMinute] )
DynamicVariables=1
FinishAction=[!UpdateMeasure MeasureTimeMOON][!Redraw]
Group=Times
Disabled=1

[MeasureMoonsetHour]
Measure=String
String=[@MoonDay1SetTime]
RegExpSubstitute=1
Substitute="^(\d{1,2}):\d{1,2}$":"\1","^$":"0"
DynamicVariables=1

[MeasureMoonsetMinute]
Measure=String
String=[@MoonDay1SetTime]
RegExpSubstitute=1
Substitute="^\d{1,2}:(\d{1,2})$":"\1","^$":"0"
DynamicVariables=1

;***ERROR: Calc: "N" is unknown***
[MeasureMoonsetMoment]
Measure=Calc
Formula=( 60 * [MeasureMoonsetHour] + [MeasureMoonsetMinute] )
DynamicVariables=1
FinishAction=[!UpdateMeasure MeasureTimeMOON][!Redraw]
Group=Times
Disabled=1

[MeasureDayLengthMOON]
Measure=Calc
Formula=(( MeasureMoonsetMoment > MeasureMoonriseMoment ) ? ( MeasureMoonsetMoment - MeasureMoonriseMoment ) : ( 1440 - MeasureMoonriseMoment + MeasureMoonsetMoment ))

[MeasureSinceMoonrise]
Measure=Calc
Formula=(( MeasureMoonsetMoment > MeasureMoonriseMoment ) ? (( 60 * MeasureHour + MeasureMinute - MeasureMoonriseMoment ) / ( 0.00001 + MeasureDayLengthMOON )) : ((( 60 * MeasureHour + MeasureMinute ) >= MeasureMoonriseMoment ) ? (( 60 * MeasureHour + MeasureMinute - MeasureMoonriseMoment ) / ( 0.00001 + MeasureDayLengthMOON )) : (( 1440 - MeasureMoonriseMoment + 60 * MeasureHour + MeasureMinute ) / ( 0.00001 + MeasureDayLengthMOON ))))

;Moon:
;Daytime=1: The sun is up/it's daytime
;HiddenMoon=1: Don't display moon ever
;HiddenMoonDay=0: Only display moon at night
[MeasureTimeMOON]
Measure=Calc
Formula=( 60 * MeasureHour + MeasureMinute )
Group=Moon
IfCondition=( ( ( ((#Daytime#=0)&&(#HiddenMoonDay#=0)) || ((#Daytime#=0)&&(#HiddenMoonDay#=1)) || ((#Daytime#=1)&&(#HiddenMoonDay#=1)) ) && (#HiddenMoon#=0) && (MeasureMoonsetMoment>MeasureMoonriseMoment) && ((#CURRENTSECTION#>=MeasureMoonriseMoment) && (#CURRENTSECTION#<MeasureMoonsetMoment)) ) || ( ( ((#Daytime#=0)&&(#HiddenMoonDay#=0)) || ((#Daytime#=0) && (#HiddenMoonDay#=1)) || ((#Daytime#=1) && (#HiddenMoonDay#=1)) ) && (#HiddenMoon#=0) && (MeasureMoonriseMoment>MeasureMoonsetMoment) && ((#CURRENTSECTION#>=MeasureMoonriseMoment) || (#CURRENTSECTION#<MeasureMoonsetMoment)) ) )
IfTrueAction=[!ShowMeter MeterMoon][!UpdateMeter MeterMoon][!Redraw][!Log "Weather skin: SHOW Moon - Daytime:#Daytime#, HiddenMoonDay:#HiddenMoonDay#,Moonrise:[MeasureMoonriseMoment], MoonSet:[MeasureMoonsetMoment], CurrentMoon:[MeasureTimeMOON], Sunrise:[MeasureSunriseMoment], Sunset:[MeasureSunsetMoment]"]
IfFalseAction=[!HideMeter MeterMoon][!UpdateMeter MeterMoon][!Redraw][!Update][!Log "Weather skin: HIDE Moon - Daytime:#Daytime#, HiddenMoonDay:#HiddenMoonDay#,Moonrise:[MeasureMoonriseMoment], MoonSet:[MeasureMoonsetMoment], CurrentMoon:[MeasureTimeMOON], Sunrise:[MeasureSunriseMoment], Sunset:[MeasureSunsetMoment]"]
DynamicVariables=1
;IfConditionMode=1
;UpdateDivider=-1
Disabled=#HiddenMoon#
