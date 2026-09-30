/* Address: ram:0004c622; name: FUN_ram_0004c622; body bytes: 232 */

void FUN_ram_0004c622(uint param_1,int param_2)

{
  short sVar1;
  short sVar2;
  uint uVar3;
  char *pcVar4;
  
  gp = 0x20004000;
  for (uVar3 = 0; uVar3 < DAT_ram_20001a61; uVar3 = uVar3 + 1 & 0xff) {
    pcVar4 = (char *)(uVar3 * 0x10 + DAT_ram_20001a58);
    if ((*pcVar4 != '\0') && (*(ushort *)(pcVar4 + 6) == param_1)) {
      if (param_2 == 7) {
        FUN_ram_0004ddde(*(undefined2 *)(pcVar4 + 2));
      }
      FUN_ram_0004d36e(pcVar4,0,param_2);
      FUN_ram_0004c420(pcVar4);
    }
  }
  if (param_2 == 0) {
    for (; uVar3 < DAT_ram_20001a60; uVar3 = uVar3 + 1 & 0xff) {
      pcVar4 = (char *)(uVar3 * 0x10 + DAT_ram_20001a58);
      if (((*pcVar4 != '\0') && (pcVar4[9] != -1)) && (*(ushort *)(pcVar4 + 6) == param_1)) {
        FUN_ram_0004c604(pcVar4);
        FUN_ram_0004d3ac(pcVar4,0x14);
        FUN_ram_0004c420(pcVar4);
      }
    }
    sVar1 = 4;
    do {
      sVar2 = sVar1 + 1;
      FUN_ram_0004c4c2(sVar1,param_1,0xff);
      sVar1 = sVar2;
    } while (sVar2 != 8);
  }
  return;
}

