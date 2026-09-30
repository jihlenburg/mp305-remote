/* Address: ram:00041cba; name: tmos_msg_receive; body bytes: 106 */

int tmos_msg_receive(uint param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  gp = 0x20004000;
  iVar4 = 0;
  iVar1 = 0;
  iVar3 = DAT_ram_20001b60;
  do {
    if (iVar3 == 0) {
      tmos_stop_task(param_1,0x8000);
      if (iVar1 != 0) {
LAB_ram_00041ce8:
        iVar3 = *(int *)(iVar1 + -8);
        if (iVar1 != DAT_ram_20001b60) {
          *(int *)(iVar4 + -8) = *(int *)(iVar1 + -8);
          iVar3 = DAT_ram_20001b60;
        }
        DAT_ram_20001b60 = iVar3;
        *(undefined4 *)(iVar1 + -8) = 0;
        *(undefined1 *)(iVar1 + -2) = 0xff;
      }
      return iVar1;
    }
    if (*(byte *)(iVar3 + -2) == param_1) {
      iVar2 = iVar3;
      if (iVar1 != 0) {
        tmos_set_event(param_1,0x8000);
        goto LAB_ram_00041ce8;
      }
    }
    else {
      iVar2 = iVar1;
      if (iVar1 == 0) {
        iVar4 = iVar3;
      }
    }
    iVar3 = *(int *)(iVar3 + -8);
    iVar1 = iVar2;
  } while( true );
}

