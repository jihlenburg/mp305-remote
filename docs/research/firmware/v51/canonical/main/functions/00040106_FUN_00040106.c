/* Address: 00040106; name: FUN_00040106; body bytes: 142 */

uint FUN_00040106(uint param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = param_1 >> 0x18;
  if ((0xfc < uVar1) || (uVar3 = param_2 >> 0x18, uVar3 < 3)) {
    return param_1;
  }
  if (uVar1 < 3) {
    return param_2;
  }
  if (uVar3 == 0xff) {
    uVar1 = FUN_0004045a(param_1);
    return uVar1;
  }
  if ((uVar3 != *(byte *)((int)param_3 + 7)) || (uVar1 != *(byte *)((int)param_3 + 3))) {
    uVar3 = 0xff - ((uint)((int)(short)(0xff - (ushort)(byte)(param_1 >> 0x18)) *
                          (int)(short)(0xff - (ushort)(byte)(param_2 >> 0x18))) >> 8);
    *(char *)(param_3 + 3) = (char)uVar3;
    if (uVar3 == 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    *(char *)((int)param_3 + 0xd) = (char)((uVar1 * 0xff) / uVar3);
  }
  iVar2 = FUN_0003ff18(param_2,param_3[1]);
  if ((iVar2 == 0) || (iVar2 = FUN_0003ff18(param_1,*param_3), iVar2 == 0)) {
    *param_3 = param_1;
    param_3[1] = param_2;
    uVar1 = FUN_0004045a(param_1 & 0xffffff | (uint)*(byte *)((int)param_3 + 0xd) << 0x18,param_2);
    param_3[2] = uVar1;
    *(char *)((int)param_3 + 0xb) = (char)param_3[3];
  }
  return param_3[2];
}

