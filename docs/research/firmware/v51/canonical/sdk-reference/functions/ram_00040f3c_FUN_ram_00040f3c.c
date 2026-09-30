/* Address: ram:00040f3c; name: FUN_ram_00040f3c; body bytes: 164 */

undefined4 FUN_ram_00040f3c(int param_1)

{
  uint *puVar1;
  int iVar2;
  
  gp = 0x20004000;
  puVar1 = *(uint **)(param_1 + 0x44);
  do {
    if (*(uint *)(param_1 + 0x48) <= puVar1) {
      return 1;
    }
    if (*(char *)(param_1 + 0xd) == '\a') {
      if (((*(char *)(param_1 + 0x28) == *(char *)(puVar1 + 1)) &&
          (*(char *)((int)puVar1 + 5) == *(char *)(param_1 + 0x55))) &&
         ((iVar2 = FUN_ram_000404da((int)puVar1 + 6,param_1 + 0x56,6), iVar2 == 1 &&
          ((*(char *)(puVar1 + 3) == *(char *)(param_1 + 0x29) &&
           (*(short *)((int)puVar1 + 0xe) == *(short *)(param_1 + 0x2a))))))) {
        gp = 0x20004000;
        return 0;
      }
    }
    else if (((*(char *)(param_1 + 0xd) == *(char *)(puVar1 + 1)) &&
             (*(char *)((int)puVar1 + 5) == *(char *)(param_1 + 0x55))) &&
            (iVar2 = FUN_ram_000404da((int)puVar1 + 6,param_1 + 0x56,6), iVar2 == 1)) {
      gp = 0x20004000;
      return 0;
    }
    puVar1 = (uint *)*puVar1;
  } while( true );
}

