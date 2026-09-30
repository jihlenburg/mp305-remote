/* Address: ram:00052b5e; name: FUN_ram_00052b5e; body bytes: 204 */

undefined4 * FUN_ram_00052b5e(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 uVar3;
  
  gp = 0x20004000;
  if ((DAT_ram_20001d9e < DAT_ram_20001d9f) &&
     (puVar2 = (undefined4 *)FUN_ram_20000040(0xb0,0x201), puVar2 != (undefined4 *)0x0)) {
    tmos_memset(puVar2,0,0xb0);
    if (param_1 == 0) {
      *(undefined1 *)(puVar2 + 2) = 0xf0;
    }
    if (DAT_ram_20001db8 == (undefined4 *)0x0) {
      DAT_ram_20001db4 = puVar2;
      DAT_ram_20001db8 = puVar2;
      DAT_ram_20001dbc = puVar2;
      *puVar2 = 0;
      DAT_ram_20001d9e = 1;
    }
    else {
      *DAT_ram_20001dbc = puVar2;
      DAT_ram_20001dbc = puVar2;
      *puVar2 = 0;
      DAT_ram_20001d9e = DAT_ram_20001d9e + 1;
    }
    *(undefined1 *)((int)puVar2 + 9) = 1;
    *(undefined1 *)((int)puVar2 + 0xb) = 0x90;
    uVar1 = DAT_ram_20001eac;
    puVar2[0x13] = DAT_ram_20001ea8;
    puVar2[0x14] = uVar1;
    *(undefined1 *)((int)puVar2 + 0x16) = 0xff;
    *(undefined1 *)((int)puVar2 + 0x7d) = 0xff;
    *(undefined1 *)(puVar2 + 0x29) = DAT_ram_20001daa;
    *(undefined1 *)(puVar2 + 0x1a) = DAT_ram_20001bd0;
    uVar3 = FUN_ram_00061d68();
    *(undefined1 *)((int)puVar2 + 0x15) = uVar3;
  }
  else {
    puVar2 = (undefined4 *)0x0;
  }
  return puVar2;
}

