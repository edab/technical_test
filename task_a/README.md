# Task A: Suggestion consideration

> The part number of AP7354 is incorrect, and I have assumed that was the _AP7354-18SF4-R7_ (changing SF to FS), that seems a closer match.

The main criteria used for the selection is to comply to the specification given for the selected sensor, and to minimize power consumption as we are designing a _battery powered device_.

In the following sections I will present the information extracted from the datasheet, and my personal considerations, used for selecting the device.

All suitable devices share some common parameters (dropout voltage, operating temperature range, etc..) and are not considered for the purpose of this selection.

>My conclusion is that is preferable to use the _[AP7354-18SF4-R7](https://github.com/edab/technical_test/blob/master/task_a/Diodes%20AP7354-18SF4-R7.pdf)_ part, because will ensure better battery life, although some point should be taken into account during the design phase:
>- As many low <img src="https://render.githubusercontent.com/render/math?math=I_q"> LDO, his PSRR performance in not brilliant, and can lead to problem on the RF section of the Radar sensor.
>- The case _X2-DFN1010-4 (Type B)_ has a the great thermal resistance and can lead to thermal shutdown.

### Radar Sensor power supply requirements

According to the _[Acconeer A111](https://github.com/edab/technical_test/blob/master/task_a/Acconeer%20A111%20datasheet.pdf)_, there are three power lanes:

- <img src="https://render.githubusercontent.com/render/math?math=V_{IO1}"> and <img src="https://render.githubusercontent.com/render/math?math=V_{IO2}">: for the RF section
- <img src="https://render.githubusercontent.com/render/math?math=V_{IO3}">: for the digital section

Considering the standard condition of <img src="https://render.githubusercontent.com/render/math?math=T_A = 25 \degree C, V_{IOx} = 1.8 V">, the following requirements should be meet:

Condition | Severity | Description
:-|:-|:-
<img src="https://render.githubusercontent.com/render/math?math=V_{IOx} < 2.0 V"> | High | Power supply maximum input voltage for avoiding permanent damages
<img src="https://render.githubusercontent.com/render/math?math=V_{IO1} < V_{IO3}"> | High | RF supply voltage should never exceed Digital  supply voltage
<img src="https://render.githubusercontent.com/render/math?math=V_{IOx} = 1.8 \pm 0.09 V"> | Medium | Operating power supply voltages for both RF and Digital
<img src="https://render.githubusercontent.com/render/math?math=I_{cc} \approx 71 mA"> | Medium | Typical current requested during continuous TX mode


### 1st criteria: Output voltage

The required nominal output voltage is 1.8V, and a quick check on the two alternatives show:

Device | Requirement | Satisfy | Min | Typ | Max | Unit
:-|:-|:-:|:-:|:-:|:-:|:-:
[AP7354-18SF4-R7](https://github.com/edab/technical_test/blob/master/task_a/Diodes%20AP7354-18SF4-R7.pdf) | Output voltage = <img src="https://render.githubusercontent.com/render/math?math=1.8 \pm 0.09 V"> | Y | 1.76 | 1.8 | 1.84 | V
[AP2112K-1.8TRG1](https://github.com/edab/technical_test/blob/master/task_a/Diodes%20AP2112K-1.8TRG1.pdf) | Output voltage = <img src="https://render.githubusercontent.com/render/math?math=1.8 \pm 0.09 V"> | Y | 1.77 | 1.8 | 1.83 | V
~~[TPS78233DDCT](https://github.com/edab/technical_test/blob/master/task_a/TI%20TPS78233DDCT.pdf)~~ | Output voltage = <img src="https://render.githubusercontent.com/render/math?math=1.8 \pm 0.09 V"> | N | - | 3.3 | - | V

It turn out that the _Texas Instrument TPS78233DDCT_ device has an output voltage of _3.3 V_, so ***it is not suitable for this applicatioMeet?n*** an will not considered furthermore.

The _line regulation_ parameter for both useful devices is the same, _0.02 %/V_.

### 2nd criteria: Output current, load regulation, load transient

The required nominal output current should be greater than `71 mA`, and a quick check on the two alternatives show:

Device | Requirement | Satisfy | Min | Typ | Max | Unit
:-|:-|:-:|:-:|:-:|:-:|:-:
[AP7354-18SF4-R7](https://github.com/edab/technical_test/blob/master/task_a/Diodes%20AP7354-18SF4-R7.pdf) | Output current > 71mA | Y | 150 | - | - | <img src="https://render.githubusercontent.com/render/math?math=mA">
[AP2112K-1.8TRG1](https://github.com/edab/technical_test/blob/master/task_a/Diodes%20AP2112K-1.8TRG1.pdf) | Output current > 71mA | Y | 600 | - | - | <img src="https://render.githubusercontent.com/render/math?math=mA">

The _Load Regulation_ parameter is important for both the _Digital_ and the _RF_ parts, and both useful devices show good values below <img src="https://render.githubusercontent.com/render/math?math=\pm 0.04 V">.

The performances under _load transients_ for both devices are adequate, but better for the _AP2112K-1.8TRG1_ device.

### 3rd criteria: Lowest <img src="https://render.githubusercontent.com/render/math?math=I_q">

The lowest Quiescent current <img src="https://render.githubusercontent.com/render/math?math=I_q">, is a basic requirement for battery powered devices, more effective during _sleep mode_, and for the two devices we can see:

Device | Requirement | Satisfy | Min | Typ | Max | Unit
:-|:-|:-:|:-:|:-:|:-:|:-:
[AP7354-18SF4-R7](https://github.com/edab/technical_test/blob/master/task_a/Diodes%20AP7354-18SF4-R7.pdf) | Lowest quiescent current | Y | - | 0.25 | 0.6 | <img src="https://render.githubusercontent.com/render/math?math=\mu A">
[AP2112K-1.8TRG1](https://github.com/edab/technical_test/blob/master/task_a/Diodes%20AP2112K-1.8TRG1.pdf) | Lowest quiescent current | N | - | 55 | 80 | <img src="https://render.githubusercontent.com/render/math?math=\mu A">

The <img src="https://render.githubusercontent.com/render/math?math=I_q"> is defined for an output current of `0mA`, and is not really useful. Sometimes this parameter mask the real behavior of a device, so the next criteria can be used for double check.

### 4th criteria: Lowest <img src="https://render.githubusercontent.com/render/math?math=I_{GND}"> under light load

It is useful to use the Ground Current <img src="https://render.githubusercontent.com/render/math?math=I_{GND}"> graphs under light load (<img src="https://render.githubusercontent.com/render/math?math=10 \to 100 \mu A">), as an additional index of the device attitude to work on battery powMeet?ered device, paying attention also on effects of temperatures and input voltages variations.

This parameter is more effective during _sleep mode_, and for the two devices we can see:

Device | Requirement | Satisfy | Min | Typ | Max | Unit
:-|:-|:-:|:-:|:-:|:-:|:-:
[AP7354-18SF4-R7](https://github.com/edab/technical_test/blob/master/task_a/Diodes%20AP7354-18SF4-R7.pdf) | Lowest ground current under light load | Y | - | 0.2 | 0.3 | <img src="https://render.githubusercontent.com/render/math?math=\mu A">
[AP2112K-1.8TRG1](https://github.com/edab/technical_test/blob/master/task_a/Diodes%20AP2112K-1.8TRG1.pdf) | Lowest ground current under light load | N | - | 55 | 65 | <img src="https://render.githubusercontent.com/render/math?math=\mu A">

### 5th criteria: Lowest <img src="https://render.githubusercontent.com/render/math?math=I_{GND}"> under nominal load

The Ground Current <img src="https://render.githubusercontent.com/render/math?math=I_{GND}"> at nominal current is to be considered during _operation_ of the device, and for the two devices we can see:

Device | Requirement | Satisfy | Min | Typ | Max | Unit
:-|:-|:-:|:-:|:-:|:-:|:-:
[AP7354-18SF4-R7](https://github.com/edab/technical_test/blob/master/task_a/Diodes%20AP7354-18SF4-R7.pdf) | Lowest quiestent current | Y | - | 20 | - | <img src="https://render.githubusercontent.com/render/math?math=\mu A">
[AP2112K-1.8TRG1](https://github.com/edab/technical_test/blob/master/task_a/Diodes%20AP2112K-1.8TRG1.pdf) | Lowest quiestent current | N | - | 80 | - | <img src="https://render.githubusercontent.com/render/math?math=\mu A">
