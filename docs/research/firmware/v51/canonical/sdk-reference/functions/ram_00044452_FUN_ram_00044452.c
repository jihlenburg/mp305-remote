/* Address: ram:00044452; name: FUN_ram_00044452; body bytes: 178 */

void FUN_ram_00044452(int param_1)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  char cVar4;
  
  gp = 0x20004000;
  pcVar2 = (char *)FUN_ram_0004df14(*(undefined2 *)(param_1 + 4));
  if (pcVar2 == (char *)0x0) {
    cVar4 = '\0';
    cVar1 = -1;
  }
  else {
    cVar1 = *pcVar2;
    cVar4 = pcVar2[0xc];
    FUN_ram_0004434e();
    FUN_ram_0004e524(pcVar2);
    FUN_ram_0004e0e6(*(undefined2 *)(param_1 + 4));
  }
  if ((DAT_ram_20001a00 == '\0') || (DAT_ram_20001a00 != cVar1)) {
    if (cVar1 != -1) {
      FUN_ram_0004403a(*(undefined1 *)(param_1 + 2),cVar1,*(undefined2 *)(param_1 + 4),
                       *(undefined1 *)(param_1 + 6),cVar4);
    }
  }
  else {
    iVar3 = FUN_ram_00043e98(cVar1,DAT_ram_20001a01);
    if (iVar3 == 0) {
      DAT_ram_20001a00 = '\0';
    }
  }
  iVar3 = FUN_ram_0004e132(*(undefined2 *)(param_1 + 4));
  if ((iVar3 == 4) && (*(short *)(param_1 + 4) == DAT_ram_20001c0a)) {
    DAT_ram_20001c0a = -1;
  }
  return;
}

