/* Address: ram:00041c74; name: tmos_msg_allocate; body bytes: 70 */

undefined4 * tmos_msg_allocate(uint param_1)

{
  undefined4 *puVar1;
  
  gp = 0x20004000;
  if (param_1 == 0) {
    return (undefined4 *)0x0;
  }
  puVar1 = (undefined4 *)FUN_ram_20000040(param_1 + 8 & 0xffff,param_1 & 0xffff | 0x4d00);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    *puVar1 = 0;
    *(short *)(puVar1 + 1) = (short)param_1;
    *(undefined1 *)((int)puVar1 + 6) = 0xff;
    puVar1 = puVar1 + 2;
  }
  return puVar1;
}

