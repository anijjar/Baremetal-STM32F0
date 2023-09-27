# UART BOOTLOADER

STM32F0 features an onboard bootloader located in system memory. We will reserve sector 0 to contain the code to jump into the bootloader. We will only flash sectors 1-15.

We need to relovate the flasg memory to sector 2. 
# APACHE 2.0 Licence
The CMSIS File was modified.

Copyright [2023] [Aman Nijjar]

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.