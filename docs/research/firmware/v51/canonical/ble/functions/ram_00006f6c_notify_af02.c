/* Address: ram:00006f6c; name: notify_af02; body bytes: 138 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Notification path using CCCD at 0x20003014 and AF02 handle at 0x20002c9a. */

void notify_af02(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uStack_18;
  int iStack_14;
  
  gp = &DAT_ram_20002000;
  uStack_18 = 0;
  iStack_14 = 0;
  iStack_14 = (*_DAT_ram_00040128)(DAT_ram_20002ffc,0x1b,param_2,0,0,_DAT_ram_00040128);
  if (iStack_14 == 0) {
    DAT_ram_20002f88 = 1;
  }
  else {
    (*_DAT_ram_0004004c)(iStack_14,param_1,param_2);
    uStack_18 = CONCAT22((short)param_2,(undefined2)uStack_18);
    iVar1 = FUN_ram_00002d34(DAT_ram_20002ffc,&uStack_18,DAT_ram_20002f44);
    if (iVar1 == 0) {
      DAT_ram_20002f88 = 0;
    }
    else {
      DAT_ram_20002f88 = 1;
      (*_DAT_ram_0004012c)(&uStack_18,0x1b);
    }
  }
  return;
}

