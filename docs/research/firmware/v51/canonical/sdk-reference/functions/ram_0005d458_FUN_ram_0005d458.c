/* Address: ram:0005d458; name: FUN_ram_0005d458; body bytes: 414 */

undefined1 FUN_ram_0005d458(char *param_1)

{
  byte bVar1;
  int iVar2;
  short sVar3;
  int *piVar4;
  
  gp = 0x20004000;
  if (*param_1 == -0x80) {
    if ((byte)param_1[1] < 0x26) {
      (*(code *)(&PTR_FUN_ram_0005d638_ram_0006c1e0)[(byte)param_1[1]])
                (*(undefined2 *)(param_1 + 2));
      gp = 0x20004000;
      return false;
    }
    gp = 0x20004000;
    return true;
  }
  if (*param_1 != -0x7f) {
    gp = 0x20004000;
    return true;
  }
  bVar1 = param_1[1];
  if (bVar1 != 0x13) {
    if (bVar1 < 0x14) {
      if (bVar1 == 8) {
        iVar2 = FUN_ram_00057ba2(*(undefined2 *)(param_1 + 2));
        if (iVar2 == 0) {
          gp = 0x20004000;
          return 2;
        }
        thunk_FUN_ram_000520f6
                  (*(undefined1 *)(iVar2 + 0x2a),*(undefined2 *)(iVar2 + 8),
                   *(char *)(iVar2 + 0x4a) != '\0');
      }
      else {
        if (bVar1 != 0xc) {
          if (bVar1 != 5) {
            gp = 0x20004000;
            return true;
          }
          iVar2 = FUN_ram_00057ba2(*(undefined2 *)(param_1 + 2));
          if (iVar2 == 0) {
            return 2;
          }
          piVar4 = *(int **)(iVar2 + 0x118);
          if (piVar4 != (int *)0x0) {
            sVar3 = *(short *)(iVar2 + 0x42);
            do {
              sVar3 = sVar3 + 1;
              piVar4 = (int *)*piVar4;
            } while (piVar4 != (int *)0x0);
            *(short *)(iVar2 + 0x42) = sVar3;
            if (sVar3 != 0) {
              thunk_FUN_ram_000522d2(1,*(undefined2 *)(iVar2 + 8));
              *(undefined2 *)(iVar2 + 0x42) = 0;
            }
          }
          thunk_FUN_ram_000520ae
                    (*(undefined1 *)(iVar2 + 0x2a),*(undefined2 *)(iVar2 + 8),
                     *(undefined1 *)(iVar2 + 0x52));
          FUN_ram_00057aca(iVar2);
          gp = 0x20004000;
          return false;
        }
        iVar2 = FUN_ram_00057ba2(*(undefined2 *)(param_1 + 2));
        if (iVar2 == 0) {
          gp = 0x20004000;
          return 2;
        }
        thunk_FUN_ram_00052146
                  (*(undefined1 *)(iVar2 + 0x2a),*(undefined2 *)(iVar2 + 8),
                   *(undefined1 *)(iVar2 + 0x4d),*(undefined2 *)(iVar2 + 0x4e),
                   *(undefined2 *)(iVar2 + 0x50));
      }
    }
    else {
      if (bVar1 != 0x30) {
        if (0x30 < bVar1) {
          if (bVar1 == 0x57) {
            FUN_ram_0006827e(*(undefined2 *)(param_1 + 2));
            gp = 0x20004000;
            return false;
          }
          gp = 0x20004000;
          return bVar1 != 0xff;
        }
        if (bVar1 == 0x1a) {
          iVar2 = FUN_ram_00057ba2(*(undefined2 *)(param_1 + 2));
          if (iVar2 != 0) {
            thunk_FUN_ram_0005224a(*(undefined1 *)(iVar2 + 0x2a));
            gp = 0x20004000;
            return false;
          }
          gp = 0x20004000;
          return 2;
        }
        gp = 0x20004000;
        return true;
      }
      iVar2 = FUN_ram_00057ba2(*(undefined2 *)(param_1 + 2));
      if (iVar2 == 0) {
        gp = 0x20004000;
        return 2;
      }
      thunk_FUN_ram_00052288(*(undefined1 *)(iVar2 + 0x2a),*(undefined2 *)(iVar2 + 8));
    }
    *(undefined1 *)(iVar2 + 0x2a) = 0;
    gp = 0x20004000;
    return false;
  }
  iVar2 = FUN_ram_00057ba2(*(undefined2 *)(param_1 + 2));
  if (iVar2 == 0) {
    gp = 0x20004000;
    return 2;
  }
  if (*(short *)(iVar2 + 0x42) != 0) {
    thunk_FUN_ram_000522d2(1,*(undefined2 *)(iVar2 + 8));
    *(undefined2 *)(iVar2 + 0x42) = 0;
    gp = 0x20004000;
    return false;
  }
  gp = 0x20004000;
  return false;
}

