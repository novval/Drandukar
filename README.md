# Добавление звука двигателя.  
На данный момент на выбор 45 звуков двигателей.  
Основано на версии Drandukar-1.1 от [@s_tavern](https://t.me/hover_ru ), которая является модификацией версии [hoverboard-firmware-hack-FOC](#hoverboard-firmware-hack-FOC) от [EFeru](https://github.com/EFeru) [hoverboard-firmware-hack-FOC](https://github.com/EFeru/hoverboard-firmware-hack-FOR).
Идея и звуки двигателя взяты у [TheDIYGuy999](https://github.com/TheDIYGuy999), [Rc_Engine_Sound](https://github.com/TheDIYGuy999/Rc_Engine_Sound) и [Rc_Engine_Sound_ESP32](https://github.com/TheDIYGuy999/Rc_Engine_Sound_ESP32).  

Звук выводится через DAC1 (PA4, к.20) к которому штатно, через транзистор подключен зуммер.
Для вывода звука наружу необходимо доработать плату.
Вариантов доработки несколько. Я использовал вариант с сохранением зуммера.
Резистор R56 выпаял и припаял к резистору R20 (у светодиода). С освободившейся площадки "забрал" сигнал DAC1, в моем случае на припаянный на вырезанные площадки в полигоне на краю платы разъем. На вторую освободившуюся площадку припаял перемычку проводком к перенесенному резистору R56. Фото ниже.
![Modification1](/docs/pictures/enginesound_dac1_modification_1.jpeg)
![Modification2](/docs/pictures/enginesound_dac1_modification_2.jpeg)
Если после такой модификации зашить штатную прошивку, то звук зуммера будет слышан в динамике :))

Если зуммер не нужен, то можно просто выпаять зуммер, диод рядом с зумером D1AR1, транзистор Q6. И запаять перемычку (зеленая стрелка) c базы на коллектор Q6.
Сигнал звука теперь удобно брать припаявшись к контактаному отверстию зуммера (синяя стрелка).
![Modification3](/docs/pictures/enginesound_dac1_modification_3.png)

Звук на динамик необходимо выводить через усилитель.  
Я в качестве УНЧ использовал плату Bluetooth от гироскутера и его же динамик.  

## Доработки платы Bluetooth в качестве УНЧ
Мне попадались два варианта плат.  
### Плата №1:  
На ней стоял усилитель ANT8110 (как правило они все похожие)  
![btpa_sch1](/docs/pictures/enginesound_btpa_sch1.jpg)  
![btpa_pcb1_2](/docs/pictures/enginesound_btpa_pcb1_2.jpg)  
![btpa_pcb1_4](/docs/pictures/enginesound_btpa_pcb1_4.jpg)  
Перерезать дорожку - красные линии.  
Запаять резистор 1к - 100к - синяя стрелка.  
На обратной стороне перерезать дорожку - красная стрелка.  
Вход звука - желтая стрелка.  
### Плата №2:  
На ней стоял усилитель MIX2052  
![btpa_sch2](/docs/pictures/enginesound_btpa_sch2.png)  
![btpa_pcb2_1](/docs/pictures/enginesound_btpa_pcb2_1.JPG)  
Перерезать две дорожки - красные линии.  
Запаять перемычку - желтая линия.  
Вход звука - сиреневая стрелка.  

## Настройки программы:  
Для включения/выключения звука в конце файла config.h есть определения:  
ENGINE_SOUND_USE : 0 - Стандартная плата без изменений.  1 - Доработанная плата для звука двигателя.  
ENGINE_SOUND_ON  : 0 - Звук двигателя выключен. 1 - Звук двигателя включен.  
BUZZER_ON_LED    : 0 - Зуммер не используется. 1 - Зуммер подключен к светодиоду.

### Выбор звука двигателя:
В файле Src\EngineSound\EngineSettings.h необходимо раскомментировать одну строку содержащую "...Start.h" - звук запуска двигателя, и только одну строку содержащую "...Idle.h" - звук холостого хода двигателя.

TODO:
- не доделан звук выключения двигателя.
- звуки старта и хх-оборотв моторов не проверены, взяты как есть у [TheDIYGuy999](https://github.com/TheDIYGuy999).

------------------------------------------------------------------------------------------------------------------

## hoverboard-firmware-hack-FOC
[![Build status](https://github.com/EFeru/hoverboard-firmware-hack-FOC/actions/workflows/build_on_commit.yml/badge.svg)](https://github.com/EFeru/hoverboard-firmware-hack-FOC/actions/workflows/build_on_commit.yml)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donate_SM.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=CU2SWN2XV9SCY&currency_code=EUR&source=url)

This repository implements Field Oriented Control (FOC) for stock hoverboards. Compared to the commutation method, this new FOC control method offers superior performance featuring:
 - reduced noise and vibrations 	
 - smooth torque output and improved motor efficiency. Thus, lower energy consumption
 - field weakening to increase maximum speed range

Table of Contents
=======================

* **Wiki:** please check the wiki pages for [Getting Started](https://github.com/EFeru/hoverboard-firmware-hack-FOC/wiki#getting-started) and for [Troubleshooting](https://github.com/EFeru/hoverboard-firmware-hack-FOC/wiki#troubleshooting)
* [Hardware](#hardware)
* [FOC Firmware](#foc-firmware)
* [Example Variants](#example-variants)
* [Projects and Links](#projects-and-links)
* [Contributions](#contributions)

#### For the hoverboard sideboard firmware, see the following repositories:
 - [hoverboard-sideboard-hack-GD](https://github.com/EFeru/hoverboard-sideboard-hack-GD)
 - [hoverboard-sideboard-hack-STM](https://github.com/EFeru/hoverboard-sideboard-hack-STM)
 
#### For the FOC controller design, see the following repository:
 - [bldc-motor-control-FOC](https://github.com/EFeru/bldc-motor-control-FOC)

#### Videos:
<table>
  <tr>
    <td><a href="https://youtu.be/IgHCcj0NgWQ" title="Hovercar" rel="noopener"><img src="/docs/pictures/videos_preview/hovercar_intro.png"></a></td>
    <td><a href="https://youtu.be/gtyqtc37r10" title="Cruise Control functionality" rel="noopener"><img src="/docs/pictures/videos_preview/cruise_control.png"></a></td>
    <td><a href="https://youtu.be/jadD0M1VBoc" title="Hovercar pedal functionality" rel="noopener"><img src="/docs/pictures/videos_preview/hovercar_pedals.png"></a></td>
  </tr>
  <tr>
    <td><a href="https://youtu.be/UnlbMrCkjnE" title="Commutation vs. FOC (constant speed)" rel="noopener"><img src="/docs/pictures/videos_preview/com_foc_const.png"></a></td> 
    <td><a href="https://youtu.be/V-_L2w10wZk" title="Commutation vs. FOC (variable speed)" rel="noopener"><img src="/docs/pictures/videos_preview/com_foc_var.png"></a></td>       
    <td><a href="https://youtu.be/tVj_lpsRirA" title="Reliable Serial Communication" rel="noopener"><img src="/docs/pictures/videos_preview/serial_com.png"></a></td>
  </tr>
</table>


---
## Hardware
 
![mainboard_pinout](/docs/pictures/mainboard_pinout.png)

The original Hardware supports two 4-pin cables that originally were connected to the two sideboards. They break out GND, 12/15V and USART2&3 of the Hoverboard mainboard. Both USART2&3 support UART, PWM, PPM, and iBUS input. Additionally, the USART2 can be used as 12bit ADC, while USART3 can be used for I2C. Note that while USART3 (right sideboard cable) is 5V tolerant, USART2 (left sideboard cable) is **not** 5V tolerant.

Typically, the mainboard brain is an [STM32F103RCT6](/docs/literature/[10]_STM32F103xC_datasheet.pdf), however some mainboards feature a [GD32F103RCT6](/docs/literature/[11]_GD32F103xx-Datasheet-Rev-2.7.pdf) which is also supported by this firmware.

For the reverse-engineered schematics of the mainboard, see [20150722_hoverboard_sch.pdf](/docs/20150722_hoverboard_sch.pdf)

 
---
## FOC Firmware
 
In this firmware 3 control types are available:
- Commutation
- SIN (Sinusoidal)
- FOC (Field Oriented Control) with the following 3 control modes:
  - **VOLTAGE MODE**: in this mode the controller applies a constant Voltage to the motors. Recommended for robotics applications or applications where a fast motor response is required.
  - **SPEED MODE**: in this mode a closed-loop controller realizes the input speed target by rejecting any of the disturbance (resistive load) applied to the motor. Recommended for robotics applications or constant speed applications.
  - **TORQUE MODE**: in this mode the input torque target is realized. This mode enables motor "freewheeling" when the torque target is `0`. Recommended for most applications with a sitting human driver.
  
#### Comparison between different control methods

|Control method| Complexity | Efficiency | Smoothness | Field Weakening | Freewheeling | Standstill hold |
|--|--|--|--|--|--|--|
|Commutation| - | - | ++ | n.a. | n.a. | + |
|Sinusoidal| + | ++ | ++ | +++ | n.a. | + |
|FOC VOLTAGE| ++ | +++ | ++ | ++ | n.a. | +<sup>(2)</sup> |
|FOC SPEED| +++ | +++ | + | ++ | n.a. | +++ |
|FOC TORQUE| +++ | +++ | +++ | ++ | +++<sup>(1)</sup> | n.a<sup>(2)</sup> |

<sup>(1)</sup> By enabling `ELECTRIC_BRAKE_ENABLE` in `config.h`, the freewheeling amount can be adjusted using the `ELECTRIC_BRAKE_MAX` parameter.<br/>
<sup>(2)</sup> The standstill hold functionality can be forced by enabling `STANDSTILL_HOLD_ENABLE` in `config.h`. 

In all FOC control modes, the controller features maximum motor speed and maximum motor current protection. This brings great advantages to fulfil the needs of many robotic applications while maintaining safe operation.


### Field Weakening / Phase Advance

 - By default the Field weakening is disabled. You can enable it in config.h file by setting the FIELD_WEAK_ENA = 1 
 - The Field Weakening is a linear interpolation from 0 to FIELD_WEAK_MAX or PHASE_ADV_MAX (depeding if FOC or SIN is selected, respectively)
 - The Field Weakening starts engaging at FIELD_WEAK_LO and reaches the maximum value at FIELD_WEAK_HI
 - The figure below shows different possible calibrations for Field Weakening / Phase Advance
 ![Field Weakening](/docs/pictures/FieldWeakening.png) 
 - If you re-calibrate the Field Weakening please take all the safety measures! The motors can spin very fast!


### Parameters
 - All the calibratable motor parameters can be found in the 'BLDC_controller_data.c'. I provided you with an already calibrated controller, but if you feel like fine tuning it feel free to do so 
 - The parameters are represented in Fixed-point data type for a more efficient code execution
 - For calibrating the fixed-point parameters use the [Fixed-Point Viewer](https://github.com/EFeru/FixedPointViewer) tool
 - The controller parameters are given in [this table](https://github.com/EFeru/bldc-motor-control-FOC/blob/master/02_Figures/paramTable.png)


### FOC Webview

To explore the controller without a Matlab/Simulink installation click on the link below:

[https://eferu.github.io/bldc-motor-control-FOC/](https://eferu.github.io/bldc-motor-control-FOC/)

---
## Example Variants

- **VARIANT_ADC**: The motors are controlled by two potentiometers connected to the Left sensor cable (long wired)
- **VARIANT_USART**: The motors are controlled via serial protocol (e.g. on USART3 right sensor cable, the short wired cable). The commands can be sent from an Arduino. Check out the [hoverserial.ino](/Arduino/hoverserial) as an example sketch.
- **VARIANT_NUNCHUK**: Wii Nunchuk offers one hand control for throttle, braking and steering. This was one of the first input device used for electric armchairs or bottle crates.
- **VARIANT_PPM**: RC remote control with PPM Sum signal.
- **VARIANT_PWM**: RC remote control with PWM signal.
- **VARIANT_IBUS**: RC remote control with Flysky iBUS protocol connected to the Left sensor cable.
- **VARIANT_HOVERCAR**: The motors are controlled by two pedals brake and throttle. Reverse is engaged by double tapping on the brake pedal at standstill. See [HOVERCAR wiki](https://github.com/EFeru/hoverboard-firmware-hack-FOC/wiki/Variant-HOVERCAR).
- **VARIANT_HOVERBOARD**: The mainboard reads the two sideboards data. The sideboards need to be flashed with the hacked version. The balancing controller is **not** yet implemented.
- **VARIANT_TRANSPOTTER**: This is for transpotter build, which is a hoverboard based transportation system. For more details on how to build it check [here](https://github.com/NiklasFauth/hoverboard-firmware-hack/wiki/Build-Instruction:-TranspOtter) and [here](https://hackaday.io/project/161891-transpotter-ng).
- **VARIANT_SKATEBOARD**: This is for skateboard build, controlled using an RC remote with PWM signal connected to the right sensor cable.

Of course the firmware can be further customized for other needs or projects.


---
## Projects and Links

- **Original firmware:** [https://github.com/lucysrausch/hoverboard-firmware-hack](https://github.com/lucysrausch/hoverboard-firmware-hack)
- **[Candas](https://github.com/Candas1/) Hoverboard Web Serial Control:** [https://github.com/Candas1/Hoverboard-Web-Serial-Control](https://github.com/Candas1/Hoverboard-Web-Serial-Control)
- **[RoboDurden's](https://github.com/RoboDurden) online compiler:** [https://pionierland.de/hoverhack/](https://pionierland.de/hoverhack/) 
- **Hoverboard hack for AT32F403RCT6 mainboards:** [https://github.com/cloidnerux/hoverboard-firmware-hack](https://github.com/cloidnerux/hoverboard-firmware-hack)
- **Hoverboard hack for split mainboards:** [https://github.com/flo199213/Hoverboard-Firmware-Hack-Gen2](https://github.com/flo199213/Hoverboard-Firmware-Hack-Gen2)
- **Hoverboard hack from BiPropellant:** [https://github.com/bipropellant](https://github.com/bipropellant)
- **Hoverboard breakout boards:** [https://github.com/Jana-Marie/hoverboard-breakout](https://github.com/Jana-Marie/hoverboard-breakout)

<a/>

- **Bobbycar** [https://github.com/larsmm/hoverboard-firmware-hack-FOC-bbcar](https://github.com/larsmm/hoverboard-firmware-hack-FOC-bbcar)
- **Wheel chair:** [https://github.com/Lahorde/steer_speed_ctrl](https://github.com/Lahorde/steer_speed_ctrl)
- **TranspOtterNG:** [https://github.com/Jan--Henrik/transpOtterNG](https://github.com/Jan--Henrik/transpOtterNG)
- **Hoverboard driver for ROS:** [https://github.com/alex-makarov/hoverboard-driver](https://github.com/alex-makarov/hoverboard-driver)
- **Ongoing OneWheel project:** [https://forum.esk8.news/t/yet-another-hoverboard-to-onewheel-project/60979/14](https://forum.esk8.news/t/yet-another-hoverboard-to-onewheel-project/60979/14)
- **ST Community:** [Custom FOC motor control](https://community.st.com/s/question/0D50X0000B28qTDSQY/custom-foc-control-current-measurement-dma-timer-interrupt-needs-review)

<a/>

- **Telegram Community:** If you are an enthusiast join our [Hooover Telegram Group](https://t.me/joinchat/BHWO_RKu2LT5ZxEkvUB8uw)

---
## Stargazers

[![Stargazers over time](https://starchart.cc/EFeru/hoverboard-firmware-hack-FOC.svg)](https://starchart.cc/EFeru/hoverboard-firmware-hack-FOC)

---
## Contributions

Every contribution to this repository is highly appreciated! Feel free to create pull requests to improve this firmware as ultimately you are going to help everyone. 

If you want to donate to keep this firmware updated, please use the link below:

[![paypal](https://www.paypalobjects.com/en_US/NL/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=CU2SWN2XV9SCY&currency_code=EUR&source=url)

---
