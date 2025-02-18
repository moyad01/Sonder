[BT_MeasureCheckBluetoothRun]
Measure=Plugin
Plugin=RunCommand
Program="#@#bluetooth\batch\bluetoothCheck.bat"
State=Hide
OutputType=UTF8
FinishAction=[!SetOption BT_MeasureCheckBluetoothString String [BT_MeasureCheckBluetoothRun]][!EnableMeasure BT_MeasureCheckBluetoothString][!UpdateMeasure BT_MeasureCheckBluetoothString][!Redraw]
UpdateDivider=-1

[BT_MeasureCheckBluetoothString]
Measure=String
DynamicVariables=1
Disabled=1
IfMatch=BT_ON
IfMatchAction=#BT_OnBluetoothCheck_On#
IfNotMatchAction=#BT_OnBluetoothCheck_Off#
OnChangeAction=[!Refresh]
UpdateDivider=-1

[BT_MeasureToggleBluetoothRun]
Measure=Plugin
Plugin=RunCommand
Program="#@#bluetooth\batch\bluetoothToggle.bat"
State=Hide
OutputType=UTF8
StartInFolder=#@#\bluetooth\batch\
FinishAction=#BT_AfterBluetoothToggle#[!SetOption BT_MeasureToggleBluetoothString String [BT_MeasureToggleBluetoothRun]][!EnableMeasure BT_MeasureToggleBluetoothString][!UpdateMeasure BT_MeasureToggleBluetoothString][!Redraw]
UpdateDivider=-1

[BT_MeasureToggleBluetoothString]
Measure=String
DynamicVariables=1
Disabled=1
IfMatch=BTT_ON
IfMatchAction=#BT_OnBluetoothToggle_On#
IfNotMatchAction=#BT_OnBluetoothToggle_Off#
UpdateDivider=-1

[BT_MeasureTurnOnBluetooth]
Measure=Plugin
Plugin=RunCommand
Program="#@#bluetooth\batch\bluetoothOn.bat"
State=Hide
OutputType=UTF8
StartInFolder=#@#\bluetooth\batch\
FinishAction=#BT_AfterBluetoothTurnedOn#
UpdateDivider=-1

[BT_MeasureTurnOffBluetooth]
Measure=Plugin
Plugin=RunCommand
Program="#@#bluetooth\batch\bluetoothOff.bat"
State=Hide
OutputType=UTF8
StartInFolder=#@#\bluetooth\batch\
FinishAction=#BT_AfterBluetoothTurnedOff#
UpdateDivider=-1