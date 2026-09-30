/* Address: CODE:6ebc; name: FUN_CODE_6ebc; body bytes: 107 */

void FUN_CODE_6ebc(undefined1 param_1)

{
  char cVar1;
  char cVar2;
  undefined1 uVar3;
  undefined1 *puVar4;
  undefined2 uVar5;
  
  puVar4 = (undefined1 *)0x448;
  DAT_EXTMEM_0448 = 0;
  cVar1 = '\0';
  do {
    uVar3 = (undefined1)((ushort)puVar4 >> 8);
    cVar2 = FUN_CODE_1dad();
    uVar5 = CONCAT11(uVar3,cVar2 * '\x04' - 0xe);
    FUN_CODE_1da9('\x03' - (((0xdU < (byte)(cVar2 * '\x04')) << 7) >> 7),uVar5);
    uVar3 = (undefined1)((ushort)uVar5 >> 8);
    FUN_CODE_1d56();
    cVar2 = FUN_CODE_1da9();
    puVar4 = (undefined1 *)CONCAT11(uVar3,cVar2 * '\x04' + -0xc);
    FUN_CODE_1da9();
    FUN_CODE_1de3();
    *puVar4 = param_1;
    cVar1 = cVar1 + '\x01';
  } while (cVar1 != '\n');
  FUN_CODE_9000(0);
  if (_1_1 != '\0') {
    _1_1 = '\0';
    FUN_CODE_a6f1(1);
    FUN_CODE_a638(1,2);
  }
  FUN_CODE_9000(1);
  FUN_CODE_8800(DAT_INTMEM_b3,0x1a,3);
  DAT_EXTMEM_059e = 1;
  DAT_EXTMEM_059f = 0xbd;
  FUN_CODE_a7c3();
  return;
}

