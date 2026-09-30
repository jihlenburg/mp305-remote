/* Address: 0005121c; name: FUN_0005121c; body bytes: 60 */

/* Recovered from stored Thumb pointer at 0007aef4; callback identification is inferred until
   reviewed. */

void FUN_0005121c(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  *(undefined4 *)(param_2 + 0x2c) = 1;
  *(undefined4 *)(param_2 + 0x30) = 1;
  uVar1 = FUN_0004a318(4);
  *(undefined4 *)(param_2 + 0x3c) = uVar1;
  uVar1 = FUN_0004a318(*(int *)(param_2 + 0x30) << 2);
  *(undefined4 *)(param_2 + 0x38) = uVar1;
  **(undefined4 **)(param_2 + 0x3c) = 0x82;
  **(undefined4 **)(param_2 + 0x38) = 0x82;
  puVar2 = (undefined4 *)
           FUN_0004f588(*(undefined4 *)(param_2 + 0x34),
                        *(int *)(param_2 + 0x2c) * *(int *)(param_2 + 0x30) * 4);
  *(undefined4 **)(param_2 + 0x34) = puVar2;
  *puVar2 = 0;
  return;
}

