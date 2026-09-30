/* Address: 000466ae; name: FUN_000466ae; body bytes: 82 */

undefined4 FUN_000466ae(int param_1)

{
  short sVar1;
  undefined4 uVar2;
  
  sVar1 = *(short *)(param_1 + 8);
  if (((((((sVar1 != 1) && (sVar1 != 2)) && (sVar1 != 3)) && ((sVar1 != 4 && (sVar1 != 5)))) &&
       ((sVar1 != 6 && ((sVar1 != 7 && (sVar1 != 8)))))) && (sVar1 != 9)) &&
     (((((sVar1 != 0xb && (sVar1 != 0xc)) && (sVar1 != 0xd)) &&
       (((sVar1 != 0xe && (sVar1 != 0x10)) &&
        ((sVar1 != 0x11 && ((sVar1 != 0x12 && (sVar1 != 0x15)))))))) && (sVar1 != 0x16)))) {
    return 0;
  }
  uVar2 = FUN_0004673a();
  return uVar2;
}

