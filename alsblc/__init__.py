import os
for path_ in os.environ['PATH'].split(os.pathsep):
    if os.path.isdir(path_):
        os.add_dll_directory(path_)

from .alsblcwrapper import ALSBaselineCorrection

__all__ = ['ALSBaselineCorrection']
