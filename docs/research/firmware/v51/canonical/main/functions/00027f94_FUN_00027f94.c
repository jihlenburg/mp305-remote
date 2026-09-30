/* Address: 00027f94; name: FUN_00027f94; body bytes: 162 */

undefined4 FUN_00027f94(int param_1,int param_2,uint param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  byte *pbVar4;
  int iVar5;
  
  uVar2 = 0;
  if (param_1 == 7) {
    pbVar4 = (byte *)(param_5 + ((int)(param_3 + ((uint)((int)param_3 >> 0x1f) >> 0x1d)) >> 3));
    iVar1 = 1;
    uVar2 = 7 - (param_3 & 7);
  }
  else if (param_1 == 8) {
    iVar1 = 2;
    pbVar4 = (byte *)(param_5 + ((int)(param_3 + ((uint)((int)param_3 >> 0x1f) >> 0x1e)) >> 2));
    uVar2 = (param_3 & 3) * -2 + 6;
  }
  else if (param_1 == 9) {
    iVar1 = 4;
    pbVar4 = (byte *)(param_5 + (int)param_3 / 2);
    uVar2 = (param_3 & 1) * -4 + 4;
  }
  else {
    if (param_1 != 10) {
      return 0;
    }
    iVar1 = 8;
    pbVar4 = (byte *)(param_5 + param_3);
  }
  for (iVar5 = 0; iVar5 < param_4; iVar5 = iVar5 + 1) {
    uVar3 = (uint)(char)((char)uVar2 - (char)iVar1);
    *(undefined4 *)(param_6 + iVar5 * 4) =
         *(undefined4 *)
          (param_2 + ((uint)(*pbVar4 >> (uVar2 & 0xff)) & (1 << iVar1) - 1U & 0xffff) * 4);
    uVar2 = uVar3;
    if ((int)uVar3 < 0) {
      pbVar4 = pbVar4 + 1;
      uVar2 = 8 - iVar1;
    }
  }
  return 1;
}

