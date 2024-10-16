////////////////////////////////////////////////////////////////////////////////
// $Id: RunManager.h 8335 2024-09-02 16:39:42Z mellinger $
// Authors: schalk@wadsworth.org, juergen.mellinger@uni-tuebingen.de
// Description: A class that manages BCI2000 data file names.
//
// $BEGIN_BCI2000_LICENSE$
//
// This file is part of BCI2000, a platform for real-time bio-signal research.
// [ Copyright (C) 2000-2023: BCI2000 team and many external contributors ]
//
// BCI2000 is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// BCI2000 is distributed in the hope that it will be useful, but
//                         WITHOUT ANY WARRANTY
// - without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
//
// $END_BCI2000_LICENSE$
////////////////////////////////////////////////////////////////////////////////
#ifndef RUN_MANAGER_H
#define RUN_MANAGER_H

#include "Environment.h"
#include "Files.h"
#include "SharedMemory.h"
#include <string>

class RunManager : private EnvironmentExtension
{
  public:
    RunManager();
    ~RunManager();
    std::string CurrentSession();    // parent path to data file without run and extension
    const std::string &CurrentRun(); // path of first data file of the run, including extension

    static std::string CurrentSession(ParamList &);

  protected:
    friend class FileWriterBase;
    std::string BeginNextFilePart(); // create a new file within the current run, and return its full path
    File& CurrentFile();             // a File object referring to the current file

  protected:
    void Publish() override;
    void Preflight() const override;
    void Initialize() override;

  private:
    std::string ConstructRun();
    static std::string DataDirectory(ParamList &);
    static std::string SubstituteParameters(const std::string &, const ParamList &);
    static std::string SubstituteVariables(const std::string &, const ParamList &);

    bool mPublished, mInWritingModule, mIsSecondaryBCI2000;
    SharedMemory* mpDataFileShm;
    mutable std::string mDataFileShmName;
    mutable int mFilePart;
    mutable File mCurrentRunFile;
    mutable std::string mCurrentRun;
    mutable std::recursive_mutex mMutex;
};

#endif // RUN_MANAGER_H
