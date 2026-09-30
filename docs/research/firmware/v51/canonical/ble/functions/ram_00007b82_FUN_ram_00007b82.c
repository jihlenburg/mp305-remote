/* Address: ram:00007b82; name: FUN_ram_00007b82; body bytes: 272 */

undefined4 FUN_ram_00007b82(undefined4 *param_1,undefined4 *param_2)

{
  ushort uVar1;
  undefined *puVar2;
  undefined4 uVar3;
  
  puVar2 = PTR_DAT_ram_20002eb8_ram_20002f48;
  gp = &DAT_ram_20002000;
  if ((PTR_DAT_ram_20002eb8_ram_20002f48 != (undefined *)0x0) &&
     (*(int *)(PTR_DAT_ram_20002eb8_ram_20002f48 + 0x18) == 0)) {
    FUN_ram_00007f90(PTR_DAT_ram_20002eb8_ram_20002f48);
  }
  if (param_2 == &DAT_ram_00009234) {
    param_2 = *(undefined4 **)(puVar2 + 4);
  }
  else if (param_2 == (undefined4 *)&DAT_ram_00009254) {
    param_2 = *(undefined4 **)(puVar2 + 8);
  }
  else if (param_2 == (undefined4 *)&DAT_ram_00009214) {
    param_2 = *(undefined4 **)(puVar2 + 0xc);
  }
  uVar1 = *(ushort *)(param_2 + 3);
  if ((uVar1 & 8) == 0) {
    if ((uVar1 & 0x10) == 0) {
      *param_1 = 9;
      *(ushort *)(param_2 + 3) = uVar1 | 0x40;
      return 0xffffffff;
    }
    if ((uVar1 & 4) != 0) {
      if ((undefined4 *)param_2[0xd] != (undefined4 *)0x0) {
        if ((undefined4 *)param_2[0xd] != param_2 + 0x11) {
          FUN_ram_000081fe(param_1);
        }
        param_2[0xd] = 0;
      }
      param_2[1] = 0;
      *(ushort *)(param_2 + 3) = *(ushort *)(param_2 + 3) & 0xffdb;
      *param_2 = param_2[4];
    }
    *(ushort *)(param_2 + 3) = *(ushort *)(param_2 + 3) | 8;
  }
  if ((param_2[4] == 0) && ((*(ushort *)(param_2 + 3) & 0x280) != 0x200)) {
    FUN_ram_00008160(param_1,param_2);
  }
  if ((*(ushort *)(param_2 + 3) & 1) == 0) {
    uVar3 = 0;
    if ((*(ushort *)(param_2 + 3) & 2) == 0) {
      uVar3 = param_2[5];
    }
    param_2[2] = uVar3;
  }
  else {
    param_2[2] = 0;
    param_2[6] = -param_2[5];
  }
  if (param_2[4] == 0) {
    if ((*(ushort *)(param_2 + 3) & 0x80) != 0) {
      *(ushort *)(param_2 + 3) = *(ushort *)(param_2 + 3) | 0x40;
      return 0xffffffff;
    }
    gp = &DAT_ram_20002000;
    return 0;
  }
  gp = &DAT_ram_20002000;
  return 0;
}

