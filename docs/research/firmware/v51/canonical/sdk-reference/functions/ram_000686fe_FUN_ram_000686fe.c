/* Address: ram:000686fe; name: FUN_ram_000686fe; body bytes: 422 */

uint FUN_ram_000686fe(undefined4 param_1,uint param_2)

{
  byte bVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  
  gp = 0x20004000;
  if ((short)param_2 < 0) {
    pcVar2 = (char *)tmos_msg_receive(DAT_ram_20001a7c);
    if (pcVar2 != (char *)0x0) {
      if (*pcVar2 == -0x6f) {
        if (pcVar2[1] == '\x0e') {
          if (((*(short *)(pcVar2 + 4) == 0x1405) && (DAT_ram_20001a80 != (undefined4 *)0x0)) &&
             ((code *)*DAT_ram_20001a80 != (code *)0x0)) {
            (*(code *)*DAT_ram_20001a80)
                      (*(undefined2 *)(*(int *)(pcVar2 + 8) + 1),
                       (int)*(char *)(*(int *)(pcVar2 + 8) + 3));
          }
        }
        else if (((((pcVar2[1] == '>') && (pcVar2[2] == '\a')) &&
                  (iVar4 = FUN_ram_0004df14(*(undefined2 *)(pcVar2 + 4)), iVar4 != 0)) &&
                 ((*(char *)(iVar4 + 0xc) == '\b' && (DAT_ram_20001a80 != (undefined4 *)0x0)))) &&
                ((code *)DAT_ram_20001a80[2] != (code *)0x0)) {
          (*(code *)DAT_ram_20001a80[2])
                    (*(undefined2 *)(pcVar2 + 4),*(short *)(pcVar2 + 6) + -4,
                     *(short *)(pcVar2 + 10) + -4);
        }
      }
      else if (*pcVar2 == -0x30) {
        bVar1 = pcVar2[2];
        if (bVar1 == 5) {
          if (pcVar2[1] == '\0') {
            FUN_ram_00069cb0(pcVar2[3],pcVar2 + 4,*(undefined2 *)(pcVar2 + 10),8);
          }
        }
        else if (bVar1 < 6) {
          if ((bVar1 == 0) && (pcVar2[1] == '\0')) {
            if (DAT_ram_20001f17 == '\0') {
              FUN_ram_00042e5e(2,0x10,&DAT_ram_20001f28);
              FUN_ram_00042e5e(3,0x10,&DAT_ram_20001f38);
              FUN_ram_00042e10(DAT_ram_200019c4);
            }
            tmos_memcpy(&DAT_ram_20001f4c,pcVar2 + 3,6);
          }
        }
        else if ((bVar1 == 6) || (bVar1 == 0xc)) {
          FUN_ram_0006a4ec();
        }
        if ((DAT_ram_20001a80 != (undefined4 *)0x0) && ((code *)DAT_ram_20001a80[1] != (code *)0x0))
        {
          (*(code *)DAT_ram_20001a80[1])(pcVar2);
        }
      }
      tmos_msg_deallocate(pcVar2);
    }
    uVar3 = 0x8000;
  }
  else {
    if (-1 < (int)(param_2 << 0x11)) {
      gp = 0x20004000;
      return 0;
    }
    FUN_ram_00042e5e(4,4,&DAT_ram_20001acc);
    FUN_ram_00042e10(DAT_ram_200019c4);
    uVar3 = 0x4000;
  }
  return uVar3 ^ param_2;
}

