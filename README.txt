©Client GmbH 2019  1 / 4 
 
 
 
Introduction and Goals 
 
Client Software estimates GNSS (Global Navigation Satellite Systems) corrections based on network observations. These corrections are transmitted from a service 
provider to the users by different communication technologies and formats. 
The following slides give an introduction to GNSS corrections. 
 ©Client GmbH 2019  2 / 4 
 
 
 ©Client GmbH 2019  3 / 4 
 
The SAPA Format is an open format realization from Sapcorda to transmit SSR corrections. The SAPA format content is based on the State State Representation (SSR) 
model with basic SSR parameters orbit, clock, biases, and atmospheric corrections for the ionosphere and troposphere, respectively. 
Client’s goal is to support as many as possible correction formats. For this purpose we need an encoder/decoder library for the SAPA format. 
So far, the SAPA format consists of three message types OCB, HPAC and Area definition (see SAPA ICD 1.5) . The OCB part has been already implemented and can be 
used as a kind of blue print for the remaining messages types. 
 
 
Requirements Overview 
The SAPA format will be supported by a program SSRM2SAPA (and counter part SAPA2SSRM) . This program consists of two main parts MC2SAPA (SAPA2MC) and SAPA 
Encoder (SAPA Decoder), respectively. 
In SSRM2SAPA the first part receives data from the internally used SSR data stream (referred as “MC stream”) and maps these data to SAPA structures (declared in 
gpp_sapa.h). The mapping is done by Client. The second part encodes data from the SAPA structures to binary according to the SAPA ICD. 
At the client’s side the SAPA Decoder decodes the binary stream to SAPA structures which will be mapped afterwards to the internally used MC stream by the 
SAPA2MC functions. 
 
  
 
The requested Client SAPA library should contain: 
•  encoder and decoder functions for SAPA messages defined in the latest SAPA ICD 
•  functions to add data to SAPA structures 
Client provides structure and prototype declarations as well as an example to the SAPA OCB implementation that should be used implement/extent the SAPA 
Encoder/Decoder library. 
 
 
Architecture Constrains 
•  programming language: C 
•  Watcom 11 Compiler (version provided by Client) 
•  Windows is preferred as Client provides a dll 