#include "comboboxmodel.h"

ComboBoxModel::ComboBoxModel(QObject *parent) : QObject(parent) {}

QStringList ComboBoxModel::items() const {
    return m_items;
}

void ComboBoxModel::setItems(const QStringList &newItems) {
    if (m_items != newItems) {
        m_items = newItems;
        emit itemsChanged();
    }
}

int ComboBoxModel::currentIndex() const {
    return m_currentIndex;
}

void ComboBoxModel::setCurrentIndex(int index) {
    if (m_currentIndex != index && index >= 0 && index < m_items.size()) {
        m_currentIndex = index;
        emit currentIndexChanged();
        emit currentTextChanged();
    }
}

QString ComboBoxModel::currentText() const {
    return (m_currentIndex >= 0 && m_currentIndex < m_items.size()) ? m_items[m_currentIndex] : "";
}

void ComboBoxModel::addItem(const QString &item) {
    if (!m_items.contains(item)) {
        m_items.append(item);
        emit itemsChanged();
    }
}

void ComboBoxModel::clearItems() {
    m_items.clear();
    m_currentIndex = -1;
    emit itemsChanged();
    emit currentIndexChanged();
    emit currentTextChanged();
}

QString ComboBoxModel::getSelectedItem() {
    return currentText();
}

/**/
void ComboBoxModel::comboBoxOpened(){
    emit signalConectedPortUpdate();

}
