
/*************************************************************************
 * Copyright (C) 2014 by Hugo Pereira Da Costa <hugo.pereira@free.fr>    *
 *                                                                       *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation; either version 2 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program; if not, write to the                         *
 * Free Software Foundation, Inc.,                                       *
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 *************************************************************************/

#include "lightlystyleconfigmodule.h"

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(Lightly::ConfigurationModule, "lightlystyleconfig.json")

#include "lightlystyleconfigmodule.moc"

namespace Lightly
{

    //_______________________________________________________________________
    ConfigurationModule::ConfigurationModule(QObject *parent, const KPluginMetaData &data)
    : KCModule(parent, data)
    {
       widget()->setLayout(new QVBoxLayout);
       widget()->layout()->addWidget( m_config = new StyleConfig(widget()));
       connect(m_config, &StyleConfig::changed, this, &KCModule::setNeedsSave);
    }

    //_______________________________________________________________________
    void ConfigurationModule::defaults()
    {
        m_config->defaults();
        KCModule::defaults();
    }

    //_______________________________________________________________________
    void ConfigurationModule::load()
    {
        m_config->load();
        KCModule::load();
    }

    //_______________________________________________________________________
    void ConfigurationModule::save()
    {
        m_config->save();
        KCModule::save();
    }

}
