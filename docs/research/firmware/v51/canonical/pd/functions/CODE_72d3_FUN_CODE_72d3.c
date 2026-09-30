/* Address: CODE:72d3; name: FUN_CODE_72d3; body bytes: 101 */

void FUN_CODE_72d3(byte *param_1,char *param_2,char param_3)

{
  bool bVar1;
  char cVar2;
  byte bVar3;
  undefined1 uVar4;
  bool bVar5;
  byte in_PSW;
  
  FUN_CODE_a340(2);
  _1_4 = in_PSW >> 7;
  FUN_CODE_9d85();
  bVar1 = _1_4 == 0;
  if (bVar1) {
    bVar3 = FUN_CODE_adc3(4);
    nop();
    nop();
    cVar2 = (bVar3 ^ *param_1) - (*param_2 - ((char)in_PSW >> 7));
  }
  else {
    cVar2 = FUN_CODE_adc3(4);
    param_2 = param_2 + -1;
    cVar2 = cVar2 - (*param_2 - ((char)in_PSW >> 7));
  }
  bVar5 = !bVar1;
  *(undefined1 *)(bVar5 + '\x01') = 0xf9;
  *(undefined1 *)(bVar5 + '\x02') = 0x72;
  uVar4 = FUN_CODE_adc3(cVar2,0xc);
  nop();
  nop();
  if (_1_4 == 0) {
    return;
  }
  *(undefined1 *)(bVar5 + '\x01') = 6;
  *(undefined1 *)(bVar5 + '\x02') = 0x73;
  FUN_CODE_adc3(0x10,uVar4);
  uVar4 = P0_0;
  nop();
  *(undefined1 *)(bVar5 + '\x01') = BANK0_R3;
  *(undefined1 *)(bVar5 + '\x02') = BANK0_R2;
  *(undefined1 *)(bVar5 + '\x03') = BANK0_R1;
  *(undefined1 *)(bVar5 + '\x04') = 0x1a;
  *(undefined1 *)(bVar5 + '\x05') = 0x73;
  FUN_CODE_ad03(param_2 + '\x10',param_3 - ((((char *)0xef < param_2) << 7) >> 7));
  *(undefined1 *)(bVar5 + '\x04') = BANK0_R7;
  uVar4 = DAT_INTMEM_b3;
  BANK0_R7 = *(undefined1 *)(bVar5 + '\x04');
  *(undefined1 *)(bVar5 + '\x04') = 0x29;
  *(undefined1 *)(bVar5 + '\x05') = 0x73;
  FUN_CODE_acbf(0,0,0,uVar4);
  BANK0_R1 = *(undefined1 *)(bVar5 + '\x03');
  BANK0_R2 = *(undefined1 *)(bVar5 + '\x02');
  BANK0_R3 = *(undefined1 *)(bVar5 + '\x01');
  *(undefined1 *)(bVar5 + '\x01') = 0x32;
  *(undefined1 *)(bVar5 + '\x02') = 0x73;
  FUN_CODE_ad23();
  return;
}

