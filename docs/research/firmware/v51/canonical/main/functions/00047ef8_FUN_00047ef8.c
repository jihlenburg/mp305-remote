/* Address: 00047ef8; name: FUN_00047ef8; body bytes: 102 */

undefined1 * FUN_00047ef8(void)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  
  FUN_00040890();
  puVar1 = (undefined1 *)FUN_0004a162(&DAT_2003a464);
  if (puVar1 != (undefined1 *)0x0) {
    FUN_0004a57a(puVar1,0,0xc4);
    puVar1[10] = puVar1[10] | 6;
    uVar2 = FUN_0005285c(0x483f9,10,puVar1);
    *(undefined4 *)(puVar1 + 0x20) = uVar2;
    uVar2 = FUN_00040890();
    *(undefined4 *)(puVar1 + 0x1c) = uVar2;
    *puVar1 = 0;
    puVar1[9] = 1;
    puVar1[0x24] = 10;
    puVar1[0x25] = 10;
    *(undefined2 *)(puVar1 + 0x28) = 400;
    *(undefined2 *)(puVar1 + 0x2a) = 100;
    puVar1[0x27] = 0x32;
    puVar1[0x26] = 3;
    *(undefined4 *)(puVar1 + 0x2c) = 0x100;
    return puVar1;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

