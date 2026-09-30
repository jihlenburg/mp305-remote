/* Address: ram:0004ed8c; name: FUN_ram_0004ed8c; body bytes: 364 */

undefined4 FUN_ram_0004ed8c(char *param_1)

{
  undefined1 *puVar1;
  int iVar2;
  undefined4 uVar3;
  char cVar4;
  
  gp = 0x20004000;
  if (*param_1 == -0x6e) {
    if (param_1[1] == '\x0e') {
      if (*(short *)(param_1 + 4) != 0x2018) {
        gp = 0x20004000;
        return 0;
      }
      if (DAT_ram_20001a68 == (char *)0x0) {
        gp = 0x20004000;
        return 0;
      }
      cVar4 = **(char **)(param_1 + 8);
      if (cVar4 == '\0') {
        if (*DAT_ram_20001a68 == '\0') {
          tmos_memcpy(DAT_ram_20001a68 + 2,*(char **)(param_1 + 8) + 1,8);
          iVar2 = thunk_FUN_ram_0006531e();
          cVar4 = '\x01';
          if (iVar2 == 0) {
            *DAT_ram_20001a68 = '\x01';
            gp = 0x20004000;
            return 1;
          }
        }
        else {
          tmos_memcpy(DAT_ram_20001a68 + 10);
        }
        if (DAT_ram_20001a68 == (char *)0x0) {
          gp = 0x20004000;
          return 1;
        }
      }
      puVar1 = (undefined1 *)tmos_msg_allocate(0x12);
      if (puVar1 != (undefined1 *)0x0) {
        *puVar1 = 0xc1;
        puVar1[1] = cVar4;
        tmos_memcpy(puVar1 + 2,DAT_ram_20001a68 + 2,0x10);
        tmos_msg_send(DAT_ram_20001a68[1],puVar1);
      }
      FUN_ram_20000104(DAT_ram_20001a68);
      DAT_ram_20001a68 = (char *)0x0;
    }
    else {
      if (param_1[1] != '>') {
        gp = 0x20004000;
        return 0;
      }
      cVar4 = param_1[2];
      if (cVar4 != '\x05') {
        if ((cVar4 != '\b') && (cVar4 != '0')) {
          gp = 0x20004000;
          return 0;
        }
        uVar3 = FUN_ram_0004e694(*(undefined2 *)(param_1 + 4),param_1[6]);
        return uVar3;
      }
      iVar2 = FUN_ram_0004e132(*(undefined2 *)(param_1 + 4));
      if (((iVar2 == 4) && (DAT_ram_20001a70 != 0)) &&
         (*(code **)(DAT_ram_20001a70 + 8) != (code *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x0004ee9e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar3 = (**(code **)(DAT_ram_20001a70 + 8))
                          (*(undefined2 *)(param_1 + 4),param_1 + 6,*(undefined2 *)(param_1 + 0xe));
        return uVar3;
      }
    }
  }
  else {
    if (*param_1 != -0x60) {
      gp = 0x20004000;
      return 0;
    }
    FUN_ram_0004ec8c();
    if (*(int *)(param_1 + 8) != 0) {
      FUN_ram_20000104();
    }
  }
  return 1;
}

