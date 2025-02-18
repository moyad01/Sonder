[Variables]
Record=(?(?=.*"lat":).*"lat":"(.*)",.*"lon":"(.*)",.*"display_name":"(.*)")

;==================== GET CITY AND LAT/LONG DATA AUTOMATICALLY ===============================
; might do this instead in future, doesn't work great for public wifi/vpn, but gives you the lat/long: https://ip-api.com/docs/api:json
[MeasureGoogleMyLocation]
Measure=WebParser
URL=https://www.google.com/search?q=what+city+am+i+in
UpdateRate=86400
Flags=ForceReload
ForceReload=1
UserAgent=Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:77.0) Gecko/20100101 Firefox/77.0
DecodeCharacterReference=1
LogSubstringErrors=0
RegExp=(?siU)data-url="\/maps\/place\/(.*)\/data
StringIndex=1
Disabled=1
RegExpSubstitute=1
Substitute="+":" ","(?siU)^(.*)( \d+)$":"\1","^$":"Could not detect"
FinishAction=[!SetVariable AutoDetectCity [MeasureGoogleMyLocation]][!WriteKeyValue Variables AutoDetectCity [MeasureGoogleMyLocation] "#@#Variables.inc"][!EnableMeasure MeasureLocations][!UpdateMeasure MeasureLocations][!Log "Googled your Location([MeasureGoogleMyLocation]), getting Lat/Long data..."]
;OnChangeAction=[!SetVariable AutoDetectCity [MeasureGoogleMyLocation]][!WriteKeyValue Variables AutoDetectCity [MeasureGoogleMyLocation] "#@#Variables.inc"][!Delay 500][!EnableMeasure MeasureLocations][!UpdateMeasure MeasureLocations][!Log "Update MeasureGoogleMyLocation Changed"]

[MeasureLocations]
Measure=WebParser
URL=https://nominatim.openstreetmap.org/search.php?q=#AutoDetectCity#&format=json
Flags=ForceReload
ForceReload=1
UserAgent=Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:78.0) Gecko/20100101 Firefox/78.0
RegExp=(?siU)#Record##Record##Record##Record#
UpdateRate=86400
Disabled=#AutoLatLong#
FinishAction=[!EnableMeasureGroup LatLongChildren][!UpdateMeasureGroup LatLongChildren][!SetVariable Latitude [MeasureLatitude1]][!WriteKeyValue Variables Latitude [MeasureLatitude1] "#@#Variables.inc"][!SetVariable Longitude [MeasureLongitude1]][!WriteKeyValue Variables Longitude [MeasureLongitude1] "#@#Variables.inc"][!Log "Latitutude and Longitude downloaded & written"][!UpdateMeter YourLat][!UpdateMeter YourLong][!Redraw][!Update][!Delay 2000][!Refresh "#ROOTCONFIG#\Weather"][!DisableMeasureGroup LatLongChildren]
;[!Delay 2000]
DynamicVariables=1

[MeasureLatitude1]
Measure=WebParser
Group=LatLongChildren
Disabled=1
URL=[MeasureLocations]
StringIndex=1
RegExpSubstitute=1
Substitute="^(.*\.)([\d]{1,6}).*$":"\1\2","":"No results"
;Maybe try this if your variables aren't being written...
;IfMatch=^$
;IfNotMatchAction=[!WriteKeyValue Variables Latitude [MeasureLatitude1] "#@#Variables.inc"]

[MeasureLongitude1]
Measure=WebParser
Group=LatLongChildren
Disabled=1
URL=[MeasureLocations]
StringIndex=2
RegExpSubstitute=1
Substitute="^(.*\.)([\d]{1,6}).*$":"\1\2"
;Maybe try this if your variables aren't being written...
;IfMatch=^$
;IfNotMatchAction=[!WriteKeyValue Variables Longitude [MeasureLongitude1] "#@#Variables.inc"]

[MeasureName1]
Measure=WebParser
Group=LatLongChildren
Disabled=1
URL=[MeasureLocations]
StringIndex=3
Substitute="":"No results"

[MeasureName2]
Measure=WebParser
Group=LatLongChildren
Disabled=1
URL=[MeasureLocations]
StringIndex=6

[MeasureLatitude2]
Measure=WebParser
Group=LatLongChildren
Disabled=1
URL=[MeasureLocations]
StringIndex=4
RegExpSubstitute=1
Substitute="^(.*\.)([\d]{1,6}).*$":"\1\2"

[MeasureLongitude2]
Measure=WebParser
Group=LatLongChildren
Disabled=1
URL=[MeasureLocations]
StringIndex=5
RegExpSubstitute=1
Substitute="^(.*\.)([\d]{1,6}).*$":"\1\2"
;IfMatch=^$
;IfNotMatchAction=[!ShowMeterGroup Group2][!UpdateMeterGroup Group2][!Redraw][!SetOption MeterBack H "([*MeterName2:YH*]+10)"][!UpdateMeter *][!Redraw]

[MeasureName3]
Measure=WebParser
Group=LatLongChildren
Disabled=1
URL=[MeasureLocations]
StringIndex=9

[MeasureLatitude3]
Measure=WebParser
Group=LatLongChildren
Disabled=1
URL=[MeasureLocations]
StringIndex=7
RegExpSubstitute=1
Substitute="^(.*\.)([\d]{1,6}).*$":"\1\2"

[MeasureLongitude3]
Measure=WebParser
Group=LatLongChildren
Disabled=1
URL=[MeasureLocations]
StringIndex=8
RegExpSubstitute=1
Substitute="^(.*\.)([\d]{1,6}).*$":"\1\2"
;IfMatch=^$
;IfNotMatchAction=[!ShowMeterGroup Group3][!UpdateMeterGroup Group3][!Redraw][!SetOption MeterBack H "([*MeterName3:YH*]+10)"][!UpdateMeter *][!Redraw]

[MeasureName4]
Measure=WebParser
Group=LatLongChildren
Disabled=1
URL=[MeasureLocations]
StringIndex=12

[MeasureLatitude4]
Measure=WebParser
Group=LatLongChildren
Disabled=1
URL=[MeasureLocations]
StringIndex=10
RegExpSubstitute=1
Substitute="^(.*\.)([\d]{1,6}).*$":"\1\2"

[MeasureLongitude4]
Measure=WebParser
Group=LatLongChildren
Disabled=1
URL=[MeasureLocations]
StringIndex=11
RegExpSubstitute=1
Substitute="^(.*\.)([\d]{1,6}).*$":"\1\2"
;IfMatch=^$
;IfNotMatchAction=[!ShowMeterGroup Group4][!UpdateMeterGroup Group4][!Redraw][!SetOption MeterBack H "([*MeterName4:YH*]+10)"][!UpdateMeter *][!Redraw]
