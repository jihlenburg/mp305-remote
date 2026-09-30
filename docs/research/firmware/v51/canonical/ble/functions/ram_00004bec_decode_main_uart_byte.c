/* Address: ram:00004bec; name: decode_main_uart_byte; body bytes: 258 */

/* AA-stuffed UART parser and checksum validation. */

void decode_main_uart_byte(uint param_1)

{
  byte bVar1;
  uint uVar2;
  
  gp = &DAT_ram_20002000;
  bVar1 = (byte)param_1;
  if (param_1 == 0xaa) {
    DAT_ram_20004561 = DAT_ram_20004561 + 1;
    if ((DAT_ram_20004561 & 1) != 0) {
      return;
    }
  }
  else if ((DAT_ram_20004561 & 1) != 0) {
    DAT_ram_20004561 = 0;
    goto switchD_ram_00004c6a_caseD_1;
  }
  switch(DAT_ram_20004668) {
  case 0:
    goto switchD_ram_00004c6a_caseD_0;
  case 1:
switchD_ram_00004c6a_caseD_1:
    DAT_ram_2000466c = bVar1;
    DAT_ram_20004565 = bVar1 & 0xf;
    DAT_ram_20004564 = (char)(param_1 >> 4);
    DAT_ram_20004668 = 4;
    return;
  case 4:
    if (param_1 != 0) {
      DAT_ram_20004562 = 0;
      DAT_ram_20004566 = (short)param_1;
      DAT_ram_20004668 = 6;
      DAT_ram_2000466c = bVar1 + DAT_ram_2000466c;
      return;
    }
    break;
  case 6:
    uVar2 = DAT_ram_20004562 + 1;
    (&DAT_ram_20004568)[DAT_ram_20004562] = bVar1;
    DAT_ram_20004562 = (byte)uVar2;
    if ((uVar2 & 0xff) < (uint)DAT_ram_20004566) {
      DAT_ram_2000466c = bVar1 + DAT_ram_2000466c;
      return;
    }
    DAT_ram_20004668 = 7;
    DAT_ram_2000466c = bVar1 + DAT_ram_2000466c;
    return;
  case 7:
    if (DAT_ram_2000466c == param_1) {
      DAT_ram_20004560 = 1;
    }
  }
  DAT_ram_20004668 = 0;
switchD_ram_00004c6a_caseD_0:
  return;
}

