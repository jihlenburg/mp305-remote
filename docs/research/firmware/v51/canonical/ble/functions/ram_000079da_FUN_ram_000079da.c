/* Address: ram:000079da; name: FUN_ram_000079da; body bytes: 218 */

undefined4 FUN_ram_000079da(int param_1,char *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  char *pcVar4;
  undefined1 *puVar5;
  
  gp = &DAT_ram_20002000;
  if ((param_1 != 0) && (*(int *)(param_1 + 0x18) == 0)) {
    FUN_ram_00007f90();
  }
  puVar2 = *(undefined4 **)(param_1 + 8);
  if (*(int *)(param_1 + 0x18) == 0) {
    FUN_ram_00007f90(param_1);
  }
  if (puVar2 == &DAT_ram_00009234) {
    puVar2 = *(undefined4 **)(param_1 + 4);
  }
  else if (puVar2 == (undefined4 *)&DAT_ram_00009254) {
    puVar2 = *(undefined4 **)(param_1 + 8);
  }
  else if (puVar2 == (undefined4 *)&DAT_ram_00009214) {
    puVar2 = *(undefined4 **)(param_1 + 0xc);
  }
  if ((((*(ushort *)(puVar2 + 3) & 8) != 0) && (puVar2[4] != 0)) ||
     (iVar3 = FUN_ram_00007b82(param_1,puVar2), iVar3 == 0)) {
    do {
      while( true ) {
        cVar1 = *param_2;
        iVar3 = puVar2[2] + -1;
        if (cVar1 == '\0') {
          puVar2[2] = iVar3;
          if (iVar3 < 0) {
            iVar3 = FUN_ram_00007ac2(param_1,10,puVar2);
            if (iVar3 == -1) {
              return 0xffffffff;
            }
          }
          else {
            puVar5 = (undefined1 *)*puVar2;
            *puVar2 = puVar5 + 1;
            *puVar5 = 10;
          }
          return 10;
        }
        puVar2[2] = iVar3;
        param_2 = param_2 + 1;
        if ((iVar3 < 0) && ((iVar3 < (int)puVar2[6] || (cVar1 == '\n')))) break;
        pcVar4 = (char *)*puVar2;
        *puVar2 = pcVar4 + 1;
        *pcVar4 = cVar1;
      }
      iVar3 = FUN_ram_00007ac2(param_1,cVar1,puVar2);
    } while (iVar3 != -1);
  }
  return 0xffffffff;
}

