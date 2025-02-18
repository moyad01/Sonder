[Variables]
;@include=#@#Variables.inc

[MeasureOnLoad]
Measure=Calc
Formula=Counter
IfCondition=MeasureOnLoad = 1
IfTrueAction=[!SetVariable RefreshOverride 0][!WriteKeyValue Variables RefreshOverride 0 "#@#Variables.inc"][!CommandMeasure StreakScript "Initialize()"][!UpdateMeasure StreakScript][!UpdateMeasure MeasureStreakActive][!SetOption "M[CurrentMonth]Day#CurrentDayMeter#Num" InlineSetting Underline][!UpdateMeter "M[CurrentMonth]Day#CurrentDayMeter#Num"][!Redraw][!Update]

[ResetRefreshOverride]
Measure=Calc
Formula=1
IfEqualValue=1
IfEqualAction=[!Delay 5000][!SetVariable RefreshOverride 0][!WriteKeyValue Variables RefreshOverride 0 "#@#Variables.inc"]
UpdateDivider=-1

[StreakScript]
Measure=Script
ScriptFile=#@#Scripts\CalendarScripts.lua
UpdateDivider=60

[CurrentDayNum]
Measure=Time
Format="%#j"
OnChangeAction=[!CommandMeasure StreakScript "Initialize()"][!UpdateMeasure MeasureStreakActive][!Redraw][!Update]

;[CurrentDayMeterChange]
;Measure=Calc
;Formula=#CurrentDayMeter#
;OnChangeAction=[!CommandMeasure StreakScript "Initialize()"][!UpdateMeasure MeasureStreakActive][!SetOption "M[CurrentMonth]Day#CurrentDayMeter#Num" InlineSetting Underline][!UpdateMeter "M[CurrentMonth]Day#CurrentDayMeter#Num"][!Redraw][!Update]
;DynamicVariables=1

[CurrentDayofMonthNum]
Measure=Time
Format="%#d"

[CurrentMonth]
Measure=Time
Format="%#m"

[CurrentYear]
Measure=Time
Format="%Y"

[MeasureLeap]
Measure=Calc
Formula=CurrentDayNum
IfCondition=([CurrentYear]%4 = 0) && (([CurrentYear]%100 <> 0) || ([CurrentYear]%400 = 0))
IfTrueAction=[!SetVariable LeapYearAdj 0][!WriteKeyValue Variables LeapYearAdj 0 "#@#Variables.inc"]
IfFalseAction=[!SetVariable LeapYearAdj 1][!WriteKeyValue Variables LeapYearAdj 1 "#@#Variables.inc"][!HideMeter M2Day60Num]
;Also need to ignore feb 29 on the streak checker if not a leap year... in the script file
IfCondition2=([CurrentMonth] <= 2) && ([CurrentDayNum] <> #CurrentDayMeter#)
IfTrueAction2=[!SetVariable CurrentDayMeter "[CurrentDayNum]"][!WriteKeyValue Variables CurrentDayMeter "[CurrentDayNum]" "#@#Variables.inc"][!Delay 50][!CommandMeasure StreakScript "Initialize()"][!UpdateMeasure MeasureStreakActive][!Redraw][!Update][!UpdateMeasure CurrentDayMeterChange2]
IfCondition3=([CurrentMonth] > 2) && ([CurrentDayNum] <> #CurrentDayMeter#)
IfTrueAction3=[!SetVariable CurrentDayMeter "([CurrentDayNum]+#LeapYearAdj#)"][!WriteKeyValue Variables CurrentDayMeter "([CurrentDayNum]+#LeapYearAdj#)" "#@#Variables.inc"][!Delay 50][!CommandMeasure StreakScript "Initialize()"][!UpdateMeasure MeasureStreakActive][!Redraw][!Update][!UpdateMeasure CurrentDayMeterChange2]
DynamicVariables=1

[CurrentDayMeterChange2]
Measure=Calc
Formula=1
IfAboveValue=0
IfAboveAction=[!CommandMeasure StreakScript "Initialize()"][!UpdateMeasure MeasureStreakActive][!SetOption "M[CurrentMonth]Day#CurrentDayMeter#Num" InlineSetting Underline][!UpdateMeter "M[CurrentMonth]Day#CurrentDayMeter#Num"][!Redraw][!Update]
DynamicVariables=1
;Disabled=1

[CalculateDayCount]
Measure=Calc
Formula=((CurrentMonth = 4) || (CurrentMonth = 6) || (CurrentMonth = 9) || (CurrentMonth = 11)) ? 30 : ((CurrentMonth = 2) ? (CalculateLeapYear ? 29 : 28) : 31)

[CalculateLeapYear]
Measure=Calc
Formula=((CurrentYear%4 = 0) && (CurrentYear%100 <> 0) || (CurrentYear%400 = 0))

;===================================================================================================================================================================================================
;============================================================================ Language month translate measures ====================================================================================
;===================================================================================================================================================================================================
[CurrentMonthName]
Measure=Time
FormatLocale=#LanguageOverride#
Format=%B

[January]
Measure=Time
TimeStamp=January
TimeStampFormat=%B
TimeStampLocale=en-US
FormatLocale=#LanguageOverride#
Format=%B
UpdateDivider=-1

[February]
Measure=Time
TimeStamp=February
TimeStampFormat=%B
TimeStampLocale=en-US
FormatLocale=#LanguageOverride#
Format=%B
UpdateDivider=-1

[March]
Measure=Time
TimeStamp=March
TimeStampFormat=%B
TimeStampLocale=en-US
FormatLocale=#LanguageOverride#
Format=%B
UpdateDivider=-1

[April]
Measure=Time
TimeStamp=April
TimeStampFormat=%B
TimeStampLocale=en-US
FormatLocale=#LanguageOverride#
Format=%B
UpdateDivider=-1

[May]
Measure=Time
TimeStamp=May
TimeStampFormat=%B
TimeStampLocale=en-US
FormatLocale=#LanguageOverride#
Format=%B
UpdateDivider=-1

[June]
Measure=Time
TimeStamp=June
TimeStampFormat=%B
TimeStampLocale=en-US
FormatLocale=#LanguageOverride#
Format=%B
UpdateDivider=-1

[July]
Measure=Time
TimeStamp=July
TimeStampFormat=%B
TimeStampLocale=en-US
FormatLocale=#LanguageOverride#
Format=%B
UpdateDivider=-1

[August]
Measure=Time
TimeStamp=August
TimeStampFormat=%B
TimeStampLocale=en-US
FormatLocale=#LanguageOverride#
Format=%B
UpdateDivider=-1

[September]
Measure=Time
TimeStamp=September
TimeStampFormat=%B
TimeStampLocale=en-US
FormatLocale=#LanguageOverride#
Format=%B
UpdateDivider=-1

[October]
Measure=Time
TimeStamp=October
TimeStampFormat=%B
TimeStampLocale=en-US
FormatLocale=#LanguageOverride#
Format=%B
UpdateDivider=-1

[November]
Measure=Time
TimeStamp=November
TimeStampFormat=%B
TimeStampLocale=en-US
FormatLocale=#LanguageOverride#
Format=%B
UpdateDivider=-1

[December]
Measure=Time
TimeStamp=December
TimeStampFormat=%B
TimeStampLocale=en-US
FormatLocale=#LanguageOverride#
Format=%B
UpdateDivider=-1

;===================================================================================================================================================================================================
;============================================================================ Month, 1st day, and current day Location measures ====================================================================
;============================================================================         only done on first load of skin           ====================================================================
;===================================================================================================================================================================================================
;==================================================== For people wondering why its a lot of repeated formulas and not referencing each other =======================================================
;==================================================== It was like that, but if rainmeter runs it all at once, some references may be behind,  ======================================================
;======================================================================== and then it will take longer to update, dumb..  ==========================================================================
;===================================================================================================================================================================================================
;0=Horizontal  1= Vertical
[UpdateMonthDayspacings]
Measure=Calc
Formula=(#CalendarLayout#)
IfCondition=(#CalendarLayout# = 0) && ((MeasureOnLoad = 1) || (#RefreshOverride# = 1))
;[M1Day1Num:X] = X=#M1Day1X#+(#DayHeight#/2)r       replaced [M1Day1Num:X] with 145
IfTrueAction=[!Log "Running: UpdateMonthDayspacingsH"][!SetVariable MonthSpacings ((#WORKAREAHEIGHT#-62)/12)][!WriteKeyValue Variables MonthSpacings ((#WORKAREAHEIGHT#-62)/12) "#@#Variables.inc"][!SetVariable DayHeight ((#SCREENAREAWIDTH#-145)/31)][!WriteKeyValue Variables DayHeight ((#SCREENAREAWIDTH#-145)/31) "#@#Variables.inc"][!UpdateMeterGroup Months]
IfCondition2=(#CalendarLayout# = 1) && ((MeasureOnLoad = 1) || (#RefreshOverride# = 1))
;replaced [M1Day1Num:Y] with 86
IfTrueAction2=[!Log "Running: UpdateMonthDayspacingsV"][!SetVariable MonthSpacings (#SCREENAREAWIDTH#/12)][!WriteKeyValue Variables MonthSpacings (#SCREENAREAWIDTH#/12) "#@#Variables.inc"][!SetVariable DayHeight ((#WORKAREAHEIGHT#-86)/31)][!WriteKeyValue Variables DayHeight ((#WORKAREAHEIGHT#-86)/31) "#@#Variables.inc"][!UpdateMeterGroup Months]
UpdateDivider=-1
DynamicVariables=1

[UpdateDayOneLocation]
Measure=Calc
Formula=(#CalendarLayout#)
IfCondition=(#CalendarLayout# = 0) && ((MeasureOnLoad = 1) || (#RefreshOverride# = 1))
IfTrueAction=[!Log "Running: DayOneLocationH"][!SetVariable DayLocationX "(((#SCREENAREAWIDTH#-145)/31)/2)"][!WriteKeyValue Variables DayLocationX "(((#SCREENAREAWIDTH#-145)/31)/2)" "#@#Variables.inc"][!SetVariable DayLocationY "(((#SCREENAREAWIDTH#-145)/31)/-2)"][!WriteKeyValue Variables DayLocationY "(((#SCREENAREAWIDTH#-145)/31)/-2)" "#@#Variables.inc"]
IfCondition2=(#CalendarLayout# = 1) && ((MeasureOnLoad = 1) || (#RefreshOverride# = 1))
IfTrueAction2=[!Log "Running: DayOneLocationV"][!SetVariable DayLocationX "(((#WORKAREAHEIGHT#-86)/31)/-2)"][!WriteKeyValue Variables DayLocationX "(((#WORKAREAHEIGHT#-86)/31)/-2)" "#@#Variables.inc"][!SetVariable DayLocationY "(((#WORKAREAHEIGHT#-86)/31)/2)"][!WriteKeyValue Variables DayLocationY "(((#WORKAREAHEIGHT#-86)/31)/2)" "#@#Variables.inc"]
UpdateDivider=-1
DynamicVariables=1

[UpdateFirstDayLocations]
Measure=Calc
Formula=(#CalendarLayout#)
IfCondition=(#CalendarLayout# = 0) && ((MeasureOnLoad = 1) || (#RefreshOverride# = 1))
IfTrueAction=[!Log "Running: FirstDayLocationsH"][!SetVariable M1Day1X 145][!SetVariable M1Day1Y 82][!SetVariable M2Day1X 145][!SetVariable M2Day1Y (82+((#WORKAREAHEIGHT#-62)/12))][!SetVariable M3Day1X 145][!SetVariable M3Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*2)][!SetVariable M4Day1X 145][!SetVariable M4Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*3)][!SetVariable M5Day1X 145][!SetVariable M5Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*4)][!SetVariable M6Day1X 145][!SetVariable M6Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*5)][!SetVariable M7Day1X 145][!SetVariable M7Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*6)][!SetVariable M8Day1X 145][!SetVariable M8Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*7)][!SetVariable M9Day1X 145][!SetVariable M9Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*8)][!SetVariable M10Day1X 145][!SetVariable M10Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*9)][!SetVariable M11Day1X 145][!SetVariable M11Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*10)][!SetVariable M12Day1X 145][!SetVariable M12Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*11)][!WriteKeyValue Variables M1Day1X 145 "#@#Variables.inc"][!WriteKeyValue Variables M1Day1Y 82 "#@#Variables.inc"][!WriteKeyValue Variables M2Day1X 145 "#@#Variables.inc"][!WriteKeyValue Variables M2Day1Y (82+((#WORKAREAHEIGHT#-62)/12)) "#@#Variables.inc"][!WriteKeyValue Variables M3Day1X 145 "#@#Variables.inc"][!WriteKeyValue Variables M3Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*2) "#@#Variables.inc"][!WriteKeyValue Variables M4Day1X 145 "#@#Variables.inc"][!WriteKeyValue Variables M4Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*3) "#@#Variables.inc"][!WriteKeyValue Variables M5Day1X 145 "#@#Variables.inc"][!WriteKeyValue Variables M5Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*4) "#@#Variables.inc"][!WriteKeyValue Variables M6Day1X 145 "#@#Variables.inc"][!WriteKeyValue Variables M6Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*5) "#@#Variables.inc"][!WriteKeyValue Variables M7Day1X 145 "#@#Variables.inc"][!WriteKeyValue Variables M7Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*6) "#@#Variables.inc"][!WriteKeyValue Variables M8Day1X 145 "#@#Variables.inc"][!WriteKeyValue Variables M8Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*7) "#@#Variables.inc"][!WriteKeyValue Variables M9Day1X 145 "#@#Variables.inc"][!WriteKeyValue Variables M9Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*8) "#@#Variables.inc"][!WriteKeyValue Variables M10Day1X 145 "#@#Variables.inc"][!WriteKeyValue Variables M10Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*9) "#@#Variables.inc"][!WriteKeyValue Variables M11Day1X 145 "#@#Variables.inc"][!WriteKeyValue Variables M11Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*10) "#@#Variables.inc"][!WriteKeyValue Variables M12Day1X 145 "#@#Variables.inc"][!WriteKeyValue Variables M12Day1Y (82+((#WORKAREAHEIGHT#-62)/12)*11) "#@#Variables.inc"]
; M1Day1X=145 - Hard coding to lock in x/y location for horizontal layout
; M1Day1Y=81.74194  = (([Month1:Y]+([Month1:H]*2))-#DayHeight#-8) - Hard coding to lock in x/y location for horizontal layout, cause above noted issues
IfCondition2=(#CalendarLayout# = 1) && ((MeasureOnLoad = 1) || (#RefreshOverride# = 1))
IfTrueAction2=[!Log "Running: FirstDayLocationsV"][!SetVariable M1Day1X (((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)][!SetVariable M1Day1Y 113][!SetVariable M2Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12))][!SetVariable M2Day1Y 113][!SetVariable M3Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*2)][!SetVariable M3Day1Y 113][!SetVariable M4Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*3)][!SetVariable M4Day1Y 113][!SetVariable M5Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*4)][!SetVariable M5Day1Y 113][!SetVariable M6Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*5)][!SetVariable M6Day1Y 113][!SetVariable M7Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*6)][!SetVariable M7Day1Y 113][!SetVariable M8Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*7)][!SetVariable M8Day1Y 113][!SetVariable M9Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*8)][!SetVariable M9Day1Y 113][!SetVariable M10Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*9)][!SetVariable M10Day1Y 113][!SetVariable M11Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*10)][!SetVariable M11Day1Y 113][!SetVariable M12Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*11)][!SetVariable M12Day1Y 113][!WriteKeyValue Variables M1Day1X (((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2) "#@#Variables.inc"][!WriteKeyValue Variables M1Day1Y 113 "#@#Variables.inc"][!WriteKeyValue Variables M2Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)) "#@#Variables.inc"][!WriteKeyValue Variables M2Day1Y 113 "#@#Variables.inc"][!WriteKeyValue Variables M3Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*2) "#@#Variables.inc"][!WriteKeyValue Variables M3Day1Y 113 "#@#Variables.inc"][!WriteKeyValue Variables M4Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*3) "#@#Variables.inc"][!WriteKeyValue Variables M4Day1Y 113 "#@#Variables.inc"][!WriteKeyValue Variables M5Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*4) "#@#Variables.inc"][!WriteKeyValue Variables M5Day1Y 113 "#@#Variables.inc"][!WriteKeyValue Variables M6Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*5) "#@#Variables.inc"][!WriteKeyValue Variables M6Day1Y 113 "#@#Variables.inc"][!WriteKeyValue Variables M7Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*6) "#@#Variables.inc"][!WriteKeyValue Variables M7Day1Y 113 "#@#Variables.inc"][!WriteKeyValue Variables M8Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*7) "#@#Variables.inc"][!WriteKeyValue Variables M8Day1Y 113 "#@#Variables.inc"][!WriteKeyValue Variables M9Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*8) "#@#Variables.inc"][!WriteKeyValue Variables M9Day1Y 113 "#@#Variables.inc"][!WriteKeyValue Variables M10Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*9) "#@#Variables.inc"][!WriteKeyValue Variables M10Day1Y 113 "#@#Variables.inc"][!WriteKeyValue Variables M11Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*10) "#@#Variables.inc"][!WriteKeyValue Variables M11Day1Y 113 "#@#Variables.inc"][!WriteKeyValue Variables M12Day1X ((((#SCREENAREAWIDTH#/12)/2)-((#WORKAREAHEIGHT#-86)/31)/2)+(#SCREENAREAWIDTH#/12)*11) "#@#Variables.inc"][!WriteKeyValue Variables M12Day1Y 113 "#@#Variables.inc"]
; M1Day1X=64.6129  =  ((#MonthSpacings#/2)-#DayHeight#/2)  -  KEEPING FORMULA BECAUSE SCREEN WIDTH SPACINGS
; M1Day1Y=112.6129  =  (([Month1:Y]+([Month1:H]*2))-#DayHeight#/2)
UpdateDivider=-1
DynamicVariables=1

;[UpdateCurrentDay]
;Measure=Calc
;Formula=(#CalendarLayout#)
;IfCondition=(#CalendarLayout# = 0) && ((MeasureOnLoad = 1) || (#RefreshOverride# = 1))
;IfTrueAction=[!DisableMeasure MeasureDayUnderline][!Delay 50][!EnableMeasure MeasureDayUnderline][!Refresh "#ROOTCONFIG#\EverydayHabitCalendar" "EverydayHabitCalendar.ini"]
;IfCondition2=(#CalendarLayout# = 1) && ((MeasureOnLoad = 1) || (#RefreshOverride# = 1))
;IfTrueAction2=[!DisableMeasure MeasureDayUnderline][!Delay 50][!EnableMeasure MeasureDayUnderline][!Refresh "#ROOTCONFIG#\EverydayHabitCalendar" "EverydayHabitCalendar.ini"]
;DynamicVariables=1
;[!Log "Running: CurrentDayH"][!WriteKeyValue Variables CurrentDayX (145+(((#SCREENAREAWIDTH#-145)/31)*0.3)+(((#SCREENAREAWIDTH#-145)/31)*([CurrentDayofMonthNum]-1))) "#@#Variables.inc"][!WriteKeyValue Variables CurrentDayY (82+([CurrentMonth]-1)*((#WORKAREAHEIGHT#-62)/12)+(((#SCREENAREAWIDTH#-145)/31)*0.1)) "#@#Variables.inc"]
;[!Log "Running: CurrentDayV..."][!WriteKeyValue Variables CurrentDayX ((#SCREENAREAWIDTH#/12)/2)+(([CurrentMonth]-1)*(#SCREENAREAWIDTH#/12)) "#@#Variables.inc"][!WriteKeyValue Variables CurrentDayY (113+(((#WORKAREAHEIGHT#-86)/31)*([CurrentDayofMonthNum]-1))-(((#WORKAREAHEIGHT#-86)/31)*0.2)) "#@#Variables.inc"]

[MeasureStreakActive]
Measure=Calc
Formula=#TodayComplete#
IfCondition=(#TodayComplete# = 0)
IfTrueAction=[!SetOption StreakCircle imagetint #StreakTodayNotCompleteColor#][!UpdateMeter StreakCircle]
IfFalseAction=[!SetOption StreakCircle imagetint #DayActiveColor#][!UpdateMeter StreakCircle]
DynamicVariables=1
;Substitute="0":"#StreakTodayNotCompleteColor#","1":"#DayActiveColor#"

; How I get data on number of Daily Active Sonder users
[MeasureRandomNumberScript]
Measure=Script
ScriptFile=#@#Scripts\RandomNumber.lua
[MeasureOnLoad]
Measure=Calc
Formula=Counter
IfCondition=MeasureOnLoad = 3
IfTrueAction=[!EnableMeasure MeasureSonderUsage][!UpdateMeasure MeasureSonderUsage][!Delay 2000][!DisableMeasure MeasureSonderUsage]
[MeasureSonderUsage]
Measure=WebParser
Flags=ForceReload
UserAgent=#UserAgent#
URL=https://www.google-analytics.com/collect?tid=UA-172309273-1&v=1&cid=#RandomNumID#&dp=%2Fsonder-EverydayCalendar&t=pageview&sr=#SCREENAREAWIDTH#x#SCREENAREAHEIGHT#&ul=#Language#
RegExp=(?siU)(.*)$
UpdateRate=-1
Disabled=1