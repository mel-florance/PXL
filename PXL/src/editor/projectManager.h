#ifndef _PROJECTMANAGER_H
#define _PROJECTMANAGER_H


class ProjectManager {
  public:
     ProjectManager();

     ~ProjectManager();

    void load(const std::string & name);

    void save(const std::string & name);

};
#endif
