/* Address: ram:0004a3f4; name: FUN_ram_0004a3f4; body bytes: 152 */

void FUN_ram_0004a3f4(int param_1,int param_2)

{
  int iVar1;
  undefined2 *puVar2;
  
  gp = 0x20004000;
  if (param_1 != 0xfffe) {
    if (param_2 == 0) {
      iVar1 = FUN_ram_0004a3c6();
      if ((iVar1 == 0) &&
         (puVar2 = (undefined2 *)FUN_ram_0004a3c6(0xffff), puVar2 != (undefined2 *)0x0)) {
        *puVar2 = (short)param_1;
      }
    }
    else {
      if (param_2 == 1) {
        puVar2 = (undefined2 *)FUN_ram_0004a3c6();
        if (puVar2 == (undefined2 *)0x0) {
          gp = 0x20004000;
          return;
        }
        *puVar2 = 0xffff;
      }
      else {
        if (param_2 != 2) {
          gp = 0x20004000;
          return;
        }
        iVar1 = linkDB_State(param_1,1);
        if (iVar1 != 0) {
          gp = 0x20004000;
          return;
        }
        puVar2 = (undefined2 *)FUN_ram_0004a3c6(param_1);
        if (puVar2 == (undefined2 *)0x0) {
          gp = 0x20004000;
          return;
        }
      }
      if (*(char *)(puVar2 + 1) != -1) {
        if (*(char *)(puVar2 + 1) != -2) {
          FUN_ram_000487a4(*(undefined1 *)((int)puVar2 + 3),param_1,0x14,0x1e,0);
        }
        FUN_ram_0004a3aa(puVar2);
        *(undefined1 *)(puVar2 + 1) = 0xff;
      }
      *(undefined1 *)(puVar2 + 2) = 0;
    }
  }
  return;
}

