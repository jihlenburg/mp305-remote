/* Address: ram:0000268a; name: FUN_ram_0000268a; body bytes: 94 */

void FUN_ram_0000268a(int param_1,undefined1 param_2,int param_3,int param_4)

{
  byte bVar1;
  uint uVar2;
  
  gp = &DAT_ram_20002000;
  bVar1 = (byte)param_1;
  if (param_4 == 0) {
    DAT_ram_40005000 = ~bVar1 & DAT_ram_40005000;
  }
  else {
    if (param_3 == 0) {
      DAT_ram_40005001 = ~bVar1 & DAT_ram_40005001;
    }
    else {
      DAT_ram_40005001 = DAT_ram_40005001 | bVar1;
    }
    uVar2 = 0;
    do {
      if ((param_1 >> (uVar2 & 0x1f) & 1U) != 0) {
        (&DAT_ram_40005004)[uVar2] = param_2;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 != 8);
    DAT_ram_40005000 = bVar1 | DAT_ram_40005000;
  }
  return;
}

