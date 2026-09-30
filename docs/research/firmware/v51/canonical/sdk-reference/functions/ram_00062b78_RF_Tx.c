/* Address: ram:00062b78; name: RF_Tx; body bytes: 682 */

/* WARNING: Removing unreachable block (ram,0x00062d72) */
/* WARNING: Removing unreachable block (ram,0x00062d68) */
/* WARNING: Removing unreachable block (ram,0x00062d90) */

undefined4 RF_Tx(int param_1,uint param_2,uint param_3,undefined1 param_4)

{
  uint *puVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  
  gp = 0x20004000;
  if (DAT_ram_20001ebc == 0) {
    uVar3 = 1;
  }
  else {
    *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f | 0x80;
    *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) & 0xffcdffff;
    *(undefined4 *)(DAT_ram_20001eb0 + 0x50) = 0x80;
    if ((DAT_ram_20001ee0 & 2) != 0) {
      do {
        do {
          uVar4 = FUN_ram_20001736();
        } while (uVar4 < 0x10);
      } while ((uint)DAT_ram_20001ece * 0x20 - 0x10 < uVar4);
    }
    DAT_ram_20001e88[0xb] = DAT_ram_20001e88[0xb] & 0xfffffffc | 1;
    if (((DAT_ram_20001ee0 & 2) == 0) && ((DAT_ram_20001eb4 & 0x40) != 0)) {
      uVar3 = 2;
      uVar4 = DAT_ram_20001eb8;
    }
    else {
      uVar3 = 0;
      uVar4 = (uint)DAT_ram_20001eb5;
    }
    FUN_ram_00062784(uVar4,uVar3);
    puVar1 = DAT_ram_20001e88;
    *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f;
    *puVar1 = *puVar1 & 0xfffffe7f | 0x100;
    *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
    iVar5 = DAT_ram_20001eb0;
    *(undefined4 *)(DAT_ram_20001eb0 + 0x50) = 0xda;
    uVar4 = (uint)DAT_ram_20001eb4;
    if (((DAT_ram_20001eb4 & 0x40) == 0) || (DAT_ram_20001eb8 - 0x2477f0 < 0x186a1)) {
      uVar3 = 0xa0;
    }
    else {
      uVar3 = 200;
    }
    *(undefined4 *)(iVar5 + 100) = uVar3;
    DAT_ram_20001ed4._0_1_ = (char)param_3;
    puVar1[2] = DAT_ram_20001ebc;
    DAT_ram_20001ed4._1_1_ = param_4;
    puVar1[1] = DAT_ram_20001ec0;
    *(uint *)(iVar5 + 4) = uVar4 & 1;
    puVar1 = DAT_ram_20001ea8;
    DAT_ram_20001ee2 = DAT_ram_20001ee2 | 2;
    if (param_1 == 0) {
      *DAT_ram_20001ea8 = param_3;
    }
    else {
      *(char *)DAT_ram_20001ea8 = (char)param_3;
      *(char *)((int)puVar1 + 1) = (char)param_2;
      tmos_memcpy((int)puVar1 + 2,param_1,param_2);
    }
    *(uint **)(DAT_ram_20001eb0 + 0x70) = DAT_ram_20001ea8;
    DAT_ram_20001e97 = 0;
    DAT_ram_20001e98 = 0;
    FUN_ram_00042570(FUN_ram_000628d8,0);
    FUN_ram_0006219c();
    DAT_ram_20001e9b = 3;
    if ((DAT_ram_20001ee0 & 2) != 0) {
      do {
      } while (*(int *)(DAT_ram_20001eb0 + 100) != 0);
      uVar4 = (*DAT_ram_20001c00)();
      puVar1 = DAT_ram_20001ea8;
      if ((DAT_ram_20001bd2 < '\0') || (DAT_ram_20001edc <= uVar4)) {
        iVar5 = -DAT_ram_20001edc;
      }
      else {
        iVar5 = -0x57400000 - DAT_ram_20001edc;
      }
      uVar4 = uVar4 + iVar5 >> 3;
      if ((DAT_ram_20001eb4 & 8) == 0) {
        uVar2 = param_2 + 2;
        param_2 = uVar2 & 0xff;
        *(char *)((int)DAT_ram_20001ea8 + 1) = (char)uVar2;
        *(undefined1 *)((int)puVar1 + param_2) = 0;
        ((undefined1 *)((int)puVar1 + param_2))[1] = (char)uVar4;
      }
      else {
        *DAT_ram_20001ea8 = uVar4 << 0x18 | 0x8002ff;
        param_2 = 2;
      }
    }
    FUN_ram_200011be(0,(int)(uint)DAT_ram_20001eb4 >> 4 & 3,param_2);
    iVar5 = DAT_ram_20001efc;
    uVar3 = 0;
    if ((*(uint *)(DAT_ram_20001efc + 0x2c) >> 1 & 1) != 0) {
      uVar4 = DAT_ram_20001eb8 - 1000;
      *(uint *)(DAT_ram_20001efc + 0x44) =
           *(uint *)(DAT_ram_20001efc + 0x44) & 0xfe0fffff | (uVar4 / 64000 & 0x1f) << 0x14;
      *(uint *)(iVar5 + 0x44) =
           (uVar4 % 64000 << 10) / 0xfa & 0x3ffff | *(uint *)(iVar5 + 0x44) & 0xfffc0000;
    }
  }
  return uVar3;
}

