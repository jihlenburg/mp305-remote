/* Address: ram:0004e694; name: FUN_ram_0004e694; body bytes: 246 */

undefined4 FUN_ram_0004e694(uint param_1,int param_2)

{
  ushort uVar1;
  ushort *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 uVar5;
  
  gp = 0x20004000;
  iVar3 = FUN_ram_0004df14();
  if (iVar3 == 0) {
    gp = 0x20004000;
    return 1;
  }
  puVar2 = *(ushort **)(iVar3 + 0x34);
  if ((puVar2 == (ushort *)0x0) || (*puVar2 != param_1)) {
LAB_ram_0004e768:
    if ((param_2 == 0) && (iVar3 = FUN_ram_0004df14(param_1), iVar3 != 0)) {
      *(byte *)(iVar3 + 4) = *(byte *)(iVar3 + 4) | 0x10;
    }
    FUN_ram_00044622(param_2,param_1);
  }
  else {
    if (*(char *)((int)puVar2 + 3) == '!') {
      iVar3 = DAT_ram_20001a70;
      if ((char)puVar2[1] != '\0') {
        uVar1 = *(ushort *)(*(int *)(puVar2 + 0x36) + 0x14);
        if (((*(int *)(puVar2 + 0x40) == 0) && ((uVar1 & 1) != 0)) &&
           ((*(ushort *)(*(int *)(puVar2 + 0x14) + 4) & 1) != 0)) {
          uVar5 = 0x22;
LAB_ram_0004e6e6:
          *(undefined1 *)((int)puVar2 + 3) = uVar5;
          gp = 0x20004000;
          return 1;
        }
        if (((uVar1 & 2) != 0) && ((*(ushort *)(*(int *)(puVar2 + 0x14) + 4) & 2) != 0)) {
          uVar5 = 0x24;
          goto LAB_ram_0004e6e6;
        }
        iVar3 = DAT_ram_20001a6c;
        if (((uVar1 & 4) != 0) && ((*(ushort *)(*(int *)(puVar2 + 0x14) + 4) & 4) != 0)) {
          uVar5 = 0x26;
          goto LAB_ram_0004e6e6;
        }
      }
      if (iVar3 == 0) {
        gp = 0x20004000;
        return 1;
      }
      if (*(code **)(iVar3 + 4) == (code *)0x0) {
        gp = 0x20004000;
        return 1;
      }
      (**(code **)(iVar3 + 4))(puVar2);
      uVar4 = 0;
      if (*(char *)((int)puVar2 + 3) != '/') {
        gp = 0x20004000;
        return 1;
      }
    }
    else {
      if (*(char *)((int)puVar2 + 3) != '*') goto LAB_ram_0004e768;
      uVar4 = 0;
      if (param_2 != 0) {
        uVar4 = 0x32;
      }
    }
    FUN_ram_0004e5a2(param_1,uVar4);
  }
  return 1;
}

