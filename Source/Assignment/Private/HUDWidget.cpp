#include "HUDWidget.h"

void UHUDWidget::SetCharacterHealthViewModel(UVMCharacterHealth* CharacterHealthVM) const
{
	OnCharacterHealthVMUpdated.Broadcast(CharacterHealthVM);
}
