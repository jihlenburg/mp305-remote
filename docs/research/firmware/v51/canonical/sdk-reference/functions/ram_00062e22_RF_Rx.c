/* Address: ram:00062e22; name: RF_Rx; body bytes: 468 */

undefined4 RF_Rx(int param_1,int param_2,undefined1 param_3,undefined1 param_4)

{
  uint *puVar1;
  uint *puVar2;
  undefined4 uVar3;
  uint uVar4;
  byte bVar5;
  
  puVar1 = DAT_ram_20001eb0;
  gp = 0x20004000;
  if (DAT_ram_20001dfc != 0) {
    return 1;
  }
  if (DAT_ram_20001ebc == 0) {
LAB_ram_00062e30:
    uVar3 = 1;
  }
  else {
    if ((*DAT_ram_20001eb0 & 3) != 0) {
      DAT_ram_20001eb0[0x14] = DAT_ram_20001eb0[0x14] & 0xfffffff8;
      *puVar1 = *puVar1 | 8;
    }
    if (((DAT_ram_20001ee0 & 4) == 0) && ((DAT_ram_20001eb4 & 0x40) != 0)) {
      bVar5 = DAT_ram_20001eb4 & 0x30 | 1;
      uVar4 = DAT_ram_20001eb8;
    }
    else {
      bVar5 = 0;
      uVar4 = (uint)DAT_ram_20001eb5;
    }
    FUN_ram_00062784(uVar4,bVar5);
    FUN_ram_00062030((int)(uint)DAT_ram_20001eb4 >> 4 & 3,DAT_ram_20001ed0,0);
    puVar1 = DAT_ram_20001e88;
    DAT_ram_20001ed4._2_1_ = param_4;
    DAT_ram_20001ed4._3_1_ = param_3;
    DAT_ram_20001e88[2] = DAT_ram_20001ebc;
    puVar1[1] = DAT_ram_20001ec0;
    puVar1 = DAT_ram_20001eb0;
    DAT_ram_20001eb0[1] = DAT_ram_20001eb4 & 1;
    if ((puVar1[1] & 1) != 0) {
      if (DAT_ram_20001ed8 == (undefined1 *)0x0) {
        DAT_ram_20001ed8 = (undefined1 *)FUN_ram_20000040(DAT_ram_20001ed1 + 2,0x49);
      }
      if (DAT_ram_20001ed8 == (undefined1 *)0x0) goto LAB_ram_00062e30;
      *DAT_ram_20001ed8 = DAT_ram_20001ed4._2_1_;
      if ((param_1 == 0) || (param_2 == 0)) {
        DAT_ram_20001ed8[1] = 0;
      }
      else {
        DAT_ram_20001ed8[1] = (char)param_2;
        tmos_memcpy(DAT_ram_20001ed8 + 2,param_1,param_2);
      }
      DAT_ram_20001eb0[0x1c] = (uint)DAT_ram_20001ed8;
    }
    FUN_ram_0006219c();
    DAT_ram_20001ee2 = DAT_ram_20001ee2 | 4;
    DAT_ram_20001e94 = 0x40;
    DAT_ram_20001e98 = 0;
    DAT_ram_20001e9b = 8;
    if (DAT_ram_20001be4 != 0) {
      tmos_start_task(DAT_ram_20001ee4,0x10,0x640);
    }
    puVar2 = DAT_ram_20001eb0;
    puVar1 = DAT_ram_20001e88;
    DAT_ram_20001e99 = 0;
    DAT_ram_20001e95 = 0;
    *DAT_ram_20001eb0 = 1;
    uVar3 = 0;
    *puVar1 = *puVar1 & 0xfffffe7f;
    *puVar1 = *puVar1 & 0xfffffe7f | 0x100;
    *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
    puVar2[0x14] = 0xd9;
  }
  return uVar3;
}

