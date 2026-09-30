/* Address: ram:0006ae86; name: FUN_ram_0006ae86; body bytes: 588 */

uint FUN_ram_0006ae86(undefined4 param_1,uint param_2)

{
  char cVar1;
  undefined2 uVar2;
  char *pcVar3;
  uint uVar4;
  undefined1 uStack_1c;
  undefined1 uStack_1b;
  undefined1 auStack_1a [6];
  undefined1 uStack_14;
  undefined1 uStack_13;
  int iVar5;
  
  gp = 0x20004000;
  if (-1 < (short)param_2) {
    if (-1 < (int)(param_2 << 0x11)) {
      if ((param_2 & 1) != 0) {
        if (DAT_ram_20001f14 != '\0') {
          uVar4 = FUN_ram_0004e200();
          if (uVar4 < (DAT_ram_20001bd3 & 3)) {
            uStack_1c = DAT_ram_20001f16;
            uStack_1b = DAT_ram_20001f24;
            tmos_memcpy(auStack_1a,&DAT_ram_20001ac4,6);
          }
          else {
            uStack_1c = 3;
          }
          uStack_14 = DAT_ram_20001f15;
          uStack_13 = DAT_ram_20001f49;
          iVar5 = FUN_ram_00047066(DAT_ram_200019cc,&uStack_1c);
          if (((iVar5 != 0) &&
              (DAT_ram_20001f20 = DAT_ram_20001f20 & 0xfffffff0 | 6,
              DAT_ram_20001abc != (undefined4 *)0x0)) && ((code *)*DAT_ram_20001abc != (code *)0x0))
          {
            (*(code *)*DAT_ram_20001abc)(DAT_ram_20001f20,0);
          }
        }
        gp = 0x20004000;
        return param_2 ^ 1;
      }
      if ((param_2 & 2) != 0) {
        if ((((DAT_ram_20001f18 & 1) != 0) &&
            (iVar5 = FUN_ram_0004737a(DAT_ram_200019cc), iVar5 != 0)) &&
           ((DAT_ram_20001f20 = DAT_ram_20001f20 & 0xffffff0f, DAT_ram_20001abc != (undefined4 *)0x0
            && ((code *)*DAT_ram_20001abc != (code *)0x0)))) {
          (*(code *)*DAT_ram_20001abc)(DAT_ram_20001f20,0);
        }
        gp = 0x20004000;
        return param_2 ^ 2;
      }
      if ((param_2 & 4) == 0) {
        gp = 0x20004000;
        return 0;
      }
      if ((((DAT_ram_20001f53 != '\0') && (iVar5 = FUN_ram_000473b6(DAT_ram_200019cc), iVar5 != 0))
          && (DAT_ram_20001f20 = DAT_ram_20001f20 & 0xfffff0ff,
             DAT_ram_20001abc != (undefined4 *)0x0)) && ((code *)*DAT_ram_20001abc != (code *)0x0))
      {
        (*(code *)*DAT_ram_20001abc)(DAT_ram_20001f20,0);
      }
      gp = 0x20004000;
      return param_2 ^ 4;
    }
    FUN_ram_00042e5e(4,4,&DAT_ram_20001acc);
    FUN_ram_00042e10(DAT_ram_200019c4);
    uVar4 = 0x4000;
    goto LAB_ram_0006aec0;
  }
  pcVar3 = (char *)tmos_msg_receive(DAT_ram_200019cc);
  if (pcVar3 != (char *)0x0) {
    if (DAT_ram_20001f17 == '\0') {
LAB_ram_0006aeb4:
      FUN_ram_0006ae24(pcVar3);
    }
    else {
      cVar1 = *pcVar3;
      if (cVar1 != -0x30) {
        if (cVar1 != -0x5e) {
          if (((cVar1 == -0x6f) && (pcVar3[1] == '\x0e')) && (*(short *)(pcVar3 + 4) == 0x1405)) {
            uVar2 = *(undefined2 *)(*(int *)(pcVar3 + 8) + 1);
            goto LAB_ram_0006aeee;
          }
          goto LAB_ram_0006aede;
        }
        goto LAB_ram_0006aeb4;
      }
      cVar1 = pcVar3[2];
      if (cVar1 == '\0') {
LAB_ram_0006aede:
        FUN_ram_0006ae24();
LAB_ram_0006af16:
        tmos_msg_send(DAT_ram_20001f52,pcVar3);
        goto LAB_ram_0006aebe;
      }
      if (cVar1 != '\x05') {
        if (cVar1 != '\b') {
          if (cVar1 == '\x06') {
            if (pcVar3[7] == '\b') goto LAB_ram_0006af16;
          }
          else if (cVar1 == '\a') {
            uVar2 = *(undefined2 *)(pcVar3 + 4);
            goto LAB_ram_0006aeee;
          }
          goto LAB_ram_0006aeb4;
        }
        goto LAB_ram_0006aede;
      }
      uVar2 = *(undefined2 *)(pcVar3 + 10);
LAB_ram_0006aeee:
      iVar5 = FUN_ram_0004df14(uVar2);
      if (iVar5 != 0) {
        if (*(char *)(iVar5 + 0xc) != '\b') goto LAB_ram_0006aeb4;
        goto LAB_ram_0006af16;
      }
    }
    tmos_msg_deallocate(pcVar3);
  }
LAB_ram_0006aebe:
  uVar4 = 0x8000;
LAB_ram_0006aec0:
  return uVar4 ^ param_2;
}

