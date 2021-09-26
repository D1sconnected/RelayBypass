# RelayBypass

Проект по созданию прошивки для управления гитарной педалью

## Структура папок

* `STM32` - прошивка под контроллеры семейства STM32
  * `Firmware` - проекты микроконтроллеров в среде `CubeIDE 1.6.0`
    * `MicroSdBootloader_STM32F101C4`
    * `MicroSdBootloader_STM32L151C8`
    * `RelayBypass_STM32F101C4`
    * `RelayBypass_STM32L151C8`
  * `SharedLibs` - платформо-независимый код и общие библиотеки
    * `MicroSdBootloader` - загрузчик
    * `RelayBypass` - основная бизнес-логика проекта
    * `sdcard` - библиотека для работы с MicroSd-картой
  * `Tests` - проект для разработки через тестирование (TDD) в `Microsoft Visual Studio 2019`
* `PIC` - прошивка под контроллеры семейста PIC
  * `Firmware` - исходный код прошивки и проект для микроконтроллера в среде `MPLAB X IDE v5.40`

