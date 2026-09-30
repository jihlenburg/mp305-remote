/* Address: 0001ef0c; name: FUN_0001ef0c; body bytes: 32 */

void FUN_0001ef0c(void)

{
  undefined1 uVar1;
  int iVar2;
  
  uVar1 = FUN_0001f026(&DAT_4001cc00);
  iVar2 = decode_transport_byte(0,uVar1);
  if (iVar2 != 0) {
    FUN_00011900(0);
    return;
  }
  return;
}

