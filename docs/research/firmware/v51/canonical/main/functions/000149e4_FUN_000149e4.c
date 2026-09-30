/* Address: 000149e4; name: FUN_000149e4; body bytes: 106 */

undefined4 FUN_000149e4(uint param_1,uint *param_2)

{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  if (param_2 != (uint *)0x0) {
    uVar1 = 0;
    do {
      if ((1 << uVar1 & param_1) != 0) {
        uVar6 = *param_2;
        uVar3 = param_2[1];
        uVar4 = param_2[2];
        puVar2 = &DAT_40051010 + uVar1;
        uVar5 = param_2[3];
        DAT_40051000 = param_2[4];
        *puVar2 = *puVar2 & 0xffff7fff;
        *puVar2 = *puVar2 & 0xffffff7f;
        *puVar2 = uVar5 | uVar6 | uVar3 | uVar4;
      }
      uVar1 = uVar1 + 1 & 0xff;
    } while (uVar1 < 0x10);
    return 0;
  }
  return 0xfffffffd;
}

