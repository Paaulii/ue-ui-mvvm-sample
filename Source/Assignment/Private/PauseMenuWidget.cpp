#include "PauseMenuWidget.h"

void UPauseMenuWidget::SetViewModel(UVMPauseMenu* PauseMenuViewModel)
{
	ViewModel = PauseMenuViewModel;
	OnViewModelUpdated.Broadcast(PauseMenuViewModel);
}