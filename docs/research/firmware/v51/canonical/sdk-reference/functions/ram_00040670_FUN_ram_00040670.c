/* Address: ram:00040670; name: FUN_ram_00040670; body bytes: 476 */

void FUN_ram_00040670(void)

{
  undefined2 uVar1;
  ushort uVar2;
  undefined2 *puVar3;
  ushort *puVar4;
  uint uVar5;
  
  gp = 0x20004000;
  if (DAT_ram_20001b94 != (code *)0x0) {
    (*DAT_ram_20001b94)();
    DAT_ram_20001b94 = (code *)0x0;
  }
  if (DAT_ram_20001b98 != (code *)0x0) {
    (*DAT_ram_20001b98)();
  }
  if (DAT_ram_20001b94 == (code *)0x0) {
    if (((DAT_ram_20001e99 & 1) != 0) && (DAT_ram_20001e99 = 0, 5 < DAT_ram_20001e9b)) {
      FUN_ram_0004135c();
      (*(&DAT_ram_20001b94)[DAT_ram_20001e9b - 3])();
    }
    if ((DAT_ram_20001ee0 & 4) != 0) {
      FUN_ram_00041a60();
    }
    if (DAT_ram_20001b9c != (code *)0x0) {
      (*DAT_ram_20001b9c)();
    }
    do {
      if (*(short *)((uint)DAT_ram_20001b64 * 2 + DAT_ram_20001bb4) != 0) break;
      uVar5 = DAT_ram_20001b64 + 1;
      DAT_ram_20001b64 = (byte)uVar5;
    } while ((uVar5 & 0xff) < (uint)DAT_ram_20001b65);
    if ((uint)DAT_ram_20001b64 < (uint)DAT_ram_20001b65) {
      puVar3 = (undefined2 *)(DAT_ram_20001bb4 + (uint)DAT_ram_20001b64 * 2);
      uVar1 = *puVar3;
      *puVar3 = 0;
      DAT_ram_20001bb0 = 0;
      uVar2 = (**(code **)(DAT_ram_20001b90 + (uint)DAT_ram_20001b64 * 4))
                        ((uint)DAT_ram_20001b64,uVar1);
      puVar4 = (ushort *)(DAT_ram_20001bb4 + (uint)DAT_ram_20001b64 * 2);
      *puVar4 = uVar2 & ~DAT_ram_20001bb0 | *puVar4;
      if (DAT_ram_20001b64 != 0) {
        DAT_ram_20001b64 = DAT_ram_20001b64 + 1;
      }
      if (DAT_ram_20001b64 < DAT_ram_20001b65) {
        gp = 0x20004000;
        return;
      }
    }
    DAT_ram_20001b64 = 0;
    if (DAT_ram_20001b94 == (code *)0x0) {
      if ((DAT_ram_20001e9d != '\0') && (DAT_ram_20001e9b == 0)) {
        DAT_ram_20001e9d = '\0';
        (*(code *)&SUB_ram_e00a2438)();
      }
      if (DAT_ram_20001c00 != 0) {
        DAT_ram_20001b74 = 0xa8c00000;
        FUN_ram_00040546();
        if ((((DAT_ram_20001be0 != 0) && (DAT_ram_20001bd1 <= DAT_ram_20001b74)) &&
            (DAT_ram_20001e9b < 6)) && (uVar5 = DAT_ram_20001ee0 & 4, (DAT_ram_20001ee0 & 4) == 0))
        {
          while( true ) {
            if ((int)(uint)DAT_ram_20001b65 <= (int)uVar5) {
              (*(code *)&LAB_ram_e008216c)();
              return;
            }
            if (*(short *)(uVar5 * 2 + DAT_ram_20001bb4) != 0) break;
            uVar5 = uVar5 + 1;
          }
        }
      }
    }
  }
  return;
}

