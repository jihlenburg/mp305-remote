/* Address: 0001ef5c; name: FUN_0001ef5c; body bytes: 184 */

void FUN_0001ef5c(void)

{
  char cVar1;
  undefined1 uVar2;
  char *pcVar3;
  int iVar4;
  undefined4 extraout_r3;
  undefined4 unaff_r4;
  
  uVar2 = FUN_0001f026(&DAT_4001d400);
  iVar4 = decode_transport_byte(1,uVar2);
  if (iVar4 == 0) {
    return;
  }
  pcVar3 = (char *)FUN_00015ed4(1);
  if ((pcVar3[4] == 'U') && (*pcVar3 == '\x03')) {
    DAT_1ffe0184 = 1;
    if (pcVar3[5] != -1) {
      DAT_1ffe0198 = 0;
    }
    DAT_1ffe0185 = pcVar3[5] == -1;
    if (pcVar3[6] == -1) {
      DAT_1ffe0186 = 1;
      return;
    }
    DAT_1ffe0186 = 0;
    DAT_1ffe0196 = 0;
    return;
  }
  cVar1 = *pcVar3;
  if (cVar1 == '\x06') {
    FUN_0001046a(&DAT_1fff9660,pcVar3,0x104,extraout_r3,unaff_r4);
    DAT_1ffe01ac = 1;
    return;
  }
  if (cVar1 == '\x01') {
    FUN_0001046a(&DAT_1fff9764,pcVar3,0x104,extraout_r3,unaff_r4);
    DAT_1ffe01ad = 1;
    return;
  }
  if (cVar1 == '\x05') {
    FUN_0001046a(&DAT_1fff9868,pcVar3,0x104,extraout_r3,unaff_r4);
    DAT_1ffe01ae = 1;
    return;
  }
  if (cVar1 == '\x03') {
    FUN_0001046a(&DAT_1fff996c,pcVar3,0x104,extraout_r3,unaff_r4);
    DAT_1ffe01af = 1;
    if (DAT_1fff9970 == '\x11') {
      FUN_00013c88(&DAT_1fff9970,DAT_1fff996e,DAT_1fff996c);
      DAT_1ffe01af = 0;
    }
  }
  return;
}

