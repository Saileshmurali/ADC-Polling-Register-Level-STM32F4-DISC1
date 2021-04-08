# ADC-Polling-Register-Level-STM32F4-DISC1
Use Pin PA0 for ADC conversion.
It works in continuous conversion mode
If you want to configure other channels for ADC1, set the corresponding pin as analog mode and use ADC1->SQR3 |= (channel<<0); to select a desired channel
