/* Address: ram:000499c4; name: FUN_ram_000499c4; body bytes: 308 */

bool FUN_ram_000499c4(undefined4 param_1,int param_2,int param_3,short *param_4)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  
  gp = 0x20004000;
  cVar1 = *(char *)(param_2 + 2);
  if (cVar1 == '\x05') {
    iVar3 = FUN_ram_000497aa(param_2,param_3,param_4);
LAB_ram_000499ee:
    if ((iVar3 != 0) || (param_3 != 1)) goto LAB_ram_00049aa4;
    bVar2 = true;
    if (((char)param_4[2] != '\n') &&
       (iVar3 = FUN_ram_000487a4(*(undefined1 *)(param_2 + 9),param_1,0,1,param_4), iVar3 == 0)) {
      iVar3 = FUN_ram_00048726(param_4,1);
      bVar2 = iVar3 == 0;
    }
  }
  else {
    if (cVar1 == '\a') {
      iVar3 = FUN_ram_0004983c(param_2,param_3,param_4);
      goto LAB_ram_000499ee;
    }
    if (cVar1 == '\t') {
      iVar3 = FUN_ram_0004934a(param_2,param_3,param_4);
      goto LAB_ram_000499ee;
    }
    if (cVar1 == '\r') {
      iVar3 = FUN_ram_000498ba(param_2,param_3,param_4);
      goto LAB_ram_000499ee;
    }
    if (cVar1 == '\x11') {
      iVar3 = FUN_ram_00049932(param_2,param_3,param_4);
      goto LAB_ram_000499ee;
    }
    if (cVar1 == '\x17') {
      if (*(char *)(param_2 + 0xc) == '\x01') {
        iVar3 = FUN_ram_00048e32();
      }
      else {
        iVar3 = FUN_ram_00048f06(param_2,param_3,param_4);
      }
      if (iVar3 != 1) {
        gp = 0x20004000;
        return true;
      }
    }
    iVar3 = 1;
LAB_ram_00049aa4:
    if (((param_3 == 9) && (*param_4 == 0)) ||
       (iVar4 = FUN_ram_000487a4(*(undefined1 *)(param_2 + 9),param_1,0,param_3,param_4), iVar4 != 0
       )) {
      bVar2 = true;
    }
    else {
      iVar4 = FUN_ram_00048726(param_4,param_3);
      bVar2 = iVar4 == 0;
    }
    if (iVar3 != 0) {
      if (iVar3 == 0x16) {
        gp = 0x20004000;
        return bVar2;
      }
      goto LAB_ram_00049a32;
    }
  }
  FUN_ram_000487a4(*(undefined1 *)(param_2 + 9),param_1,0x1a,*(undefined1 *)(param_2 + 2),0);
LAB_ram_00049a32:
  FUN_ram_000495b2(param_2);
  return bVar2;
}

