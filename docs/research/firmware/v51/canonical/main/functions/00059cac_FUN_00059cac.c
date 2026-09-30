/* Address: 00059cac; name: FUN_00059cac; body bytes: 212 */

void FUN_00059cac(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_28;
  code *local_24;
  int local_20;
  undefined4 uStack_1c;
  undefined1 auStack_18 [8];
  
  while (iVar3 = FUN_0006691c(DAT_1ffe0040,&local_28,0), iVar3 != 0) {
    if ((-1 < local_28) || ((*local_24)(local_20,uStack_1c), -1 < local_28)) {
      iVar3 = local_20;
      if (*(int *)(local_20 + 0x14) != 0) {
        FUN_00065666(local_20 + 4);
      }
      iVar1 = FUN_00059e40(auStack_18);
      switch(local_28) {
      case 1:
      case 2:
      case 6:
      case 7:
        *(byte *)(iVar3 + 0x24) = *(byte *)(iVar3 + 0x24) | 1;
        iVar2 = FUN_00059c18(iVar3,local_24 + *(int *)(iVar3 + 0x18),iVar1,local_24);
        if (iVar2 != 0) {
          if ((int)((uint)*(byte *)(iVar3 + 0x24) << 0x1d) < 0) {
            FUN_00059dfc(iVar3,local_24 + *(int *)(iVar3 + 0x18),iVar1);
          }
          else {
            *(byte *)(iVar3 + 0x24) = *(byte *)(iVar3 + 0x24) & 0xfe;
          }
          (**(code **)(iVar3 + 0x20))(iVar3);
        }
        break;
      case 3:
      case 8:
        *(byte *)(iVar3 + 0x24) = *(byte *)(iVar3 + 0x24) & 0xfe;
        break;
      case 4:
      case 9:
        *(byte *)(iVar3 + 0x24) = *(byte *)(iVar3 + 0x24) | 1;
        *(code **)(iVar3 + 0x18) = local_24;
        FUN_00059c18(iVar3,local_24 + iVar1,iVar1);
        break;
      case 5:
        if ((int)((uint)*(byte *)(iVar3 + 0x24) << 0x1e) < 0) {
          *(byte *)(iVar3 + 0x24) = *(byte *)(iVar3 + 0x24) & 0xfe;
        }
        else {
          FUN_00065758(iVar3);
        }
      }
    }
  }
  return;
}

