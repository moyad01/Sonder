[Variables]
;Fade=#GlobalSkinBackgroundAlphaInactive#
;Speed=10
;Action=[!UpdateMeasure "MeasureFade"][!UpdateMeter Background][!Redraw][!Update]

[Background]
Meter=IMAGE
ImageName=#@#Images\SkinBackground.White.png
ScaleMargins=12,12,12,12
;ImageAlpha=#Fade#
ImageAlpha=#GlobalSkinBackgroundAlphaInactive#
;MouseOverAction=[!CommandMeasure MeasureFade "Stop 2"][!CommandMeasure MeasureFade "Execute 1"]
MouseOverAction=[!SetOption #CURRENTSECTION# ImageAlpha #GlobalSkinBackgroundAlpha#][!UpdateMeter #CURRENTSECTION#][!Redraw]
;MouseLeaveAction=[!CommandMeasure MeasureFade "Stop 1"][!CommandMeasure MeasureFade "Execute 2"]
MouseLeaveAction=[!SetOption #CURRENTSECTION# ImageAlpha #GlobalSkinBackgroundAlphaInactive#][!UpdateMeter #CURRENTSECTION#][!Redraw]
X=(#scale#*8)
Y=(#scale#*(#Month_YAdj_All#+80))
W=(#scale#*285)
H=(#scale#*200)
imagetint=#GlobalSkinBackgroundColorTint#
;DynamicVariables=1
;LeftMouseUpAction=[!ActivateConfig "#ROOTCONFIG#\EverydayHabitCalendar\" "MonthHabitCalendar+5Habits.ini"]

;[MeasureFade]
;Measure=Plugin
;Plugin=ActionTimer
;ActionList1=Repeat FadeIn,#Speed#,25
;FadeIn=[!SetVariable Fade "(Clamp((#Fade#+10),#GlobalSkinBackgroundAlphaInactive#,#GlobalSkinBackgroundAlpha#))"]#Action#
;ActionList2=Repeat FadeOut,#Speed#,25
;FadeOut=[!SetVariable Fade "(Clamp((#Fade#-10),#GlobalSkinBackgroundAlphaInactive#,#GlobalSkinBackgroundAlpha#))"]#Action#
;DynamicVariables=1