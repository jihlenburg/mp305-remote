/* Address: CODE:9321; name: FUN_CODE_9321; body bytes: 31 */

void FUN_CODE_9321(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  
  if (DAT_INTMEM_cc == '\x03') {
    uVar2 = 0xb8;
    uVar1 = 0xb;
  }
  else {
    if (DAT_INTMEM_cc != '\x02') {
      return;
    }
    uVar2 = 0xdc;
    uVar1 = 5;
  }
  FUN_CODE_93fa(uVar1,uVar2,0x13,0x88);
  FUN_CODE_866f();
  return;
}

