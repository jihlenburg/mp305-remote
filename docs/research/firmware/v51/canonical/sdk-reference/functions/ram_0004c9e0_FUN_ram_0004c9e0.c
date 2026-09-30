/* Address: ram:0004c9e0; name: FUN_ram_0004c9e0; body bytes: 224 */

uint FUN_ram_0004c9e0(undefined4 param_1,uint param_2)

{
  char *pcVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  char *pcVar5;
  char cVar6;
  byte bVar7;
  byte bVar8;
  
  gp = 0x20004000;
  if ((short)param_2 < 0) {
    pcVar1 = (char *)tmos_msg_receive(DAT_ram_20001cc8);
    if (pcVar1 != (char *)0x0) {
      if (*pcVar1 == -0x70) {
        if (pcVar1[1] == '\x13') {
          pcVar5 = pcVar1 + 6;
          bVar4 = false;
          bVar8 = DAT_ram_20001a62;
          for (cVar6 = '\0'; pcVar1[2] != cVar6; cVar6 = cVar6 + '\x01') {
            bVar7 = bVar8 + *pcVar5;
            bVar8 = DAT_ram_20001bcb;
            if (bVar7 < DAT_ram_20001bcb) {
              bVar8 = bVar7;
            }
            pcVar5 = pcVar5 + 2;
            bVar4 = true;
          }
          if (bVar4) {
            DAT_ram_20001a62 = bVar8;
          }
          if (DAT_ram_20001a62 != 0) {
            tmos_set_event(DAT_ram_20001cc8,1);
          }
        }
        else {
          FUN_ram_0004d0a0();
        }
      }
      tmos_msg_deallocate(pcVar1);
    }
    uVar2 = param_2 ^ 0x8000;
  }
  else {
    uVar2 = 0;
    if ((param_2 & 1) != 0) {
      iVar3 = FUN_ram_0004d99c(0);
      if ((iVar3 != 0) && (DAT_ram_20001a62 != 0)) {
        tmos_set_event(DAT_ram_20001cc8,1);
      }
      uVar2 = param_2 ^ 1;
    }
  }
  return uVar2;
}

